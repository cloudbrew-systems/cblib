/*
CloudBrew - Software Defined Distributed Public Cloud Storage
Perform file split and encryption for upload.

File:	cbUpload_node.cpp
Author:	Runcy Oommen
Date:	02/17/2016

Copyright 2016 CloudBrew Systems. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbUpload.h"
#include "cbDefines.h"
#include "fileHandling.h"
#include "MemMgr.h"
#include "cJSON.h"
#include "accountHandling.h"
#include "brewEngine.h"

/* Imp Note (06/27/2016): Don't get mistaken by the extension of .cpp. This is essentially a .c file with prettymuch straight forward C code renamed as .cpp to compile with node-gyp for creating the node module */

char *cb_upload(char *uploadInfo)
{
	char *response = (char *)MEM_XMALLOC(MAX_LEN*10);
	char cmd[MAX_CMD_LEN] = {'\0'}, typeRaw[BYTE_LEN] = {'\0'}, userIdRaw[SHORT_LEN] = {'\0'}, fileNameRaw[MAX_LEN] = {'\0'}, fileAbsLocRaw[MAX_CMD_LEN] = {'\0'}, encryptedRaw[NIBBLE_LEN] = {'\0'}, splitRaw[NIBBLE_LEN] = {'\0'};
	char linkedAccountsJSON[MAX_LEN*20] = {'\0'}; /* Size allocation to be increased to a more realistic limit as and when required. It will give segfault otherwise for a bigger JSON */
	char *accountName = (char *)MEM_XMALLOC(SHORT_LEN);
	char splitFileName[MAX_LEN] = {'\0'}, splitFileAbsLoc[MAX_LEN] = {'\0'}, fileSplitState[MAX_LEN*10] = {'\0'};

	cJSON *cjson_UploadInfo = cJSON_Parse(uploadInfo);

	/* Get the type */
	cJSON *cjson_Type = cJSON_GetObjectItem(cjson_UploadInfo, TYPE);
	snprintf(typeRaw, BYTE_LEN, "%s", cJSON_Print(cjson_Type));
	char *type = brewEngine_CleanupQuotes(typeRaw);

	/* Get the encrypted flag */
	cJSON *cjson_Encrypted = cJSON_GetObjectItem(cjson_UploadInfo, ENCRYPTED);
	snprintf(encryptedRaw, NIBBLE_LEN, "%s", cJSON_Print(cjson_Encrypted));
	char *encrypted = brewEngine_CleanupQuotes(encryptedRaw);

	/* Get the split flag */
	cJSON *cjson_Split = cJSON_GetObjectItem(cjson_UploadInfo, SPLIT);
	snprintf(splitRaw, NIBBLE_LEN, "%s", cJSON_Print(cjson_Split));
	char *split = brewEngine_CleanupQuotes(splitRaw);

	/* Get the userId */
	cJSON *cjson_UserId = cJSON_GetObjectItem(cjson_UploadInfo, UID);
	snprintf(userIdRaw, SHORT_LEN, "%s", cJSON_Print(cjson_UserId));
	char *userId = brewEngine_CleanupQuotes(userIdRaw);

	/* Get the fileName */
	cJSON *cjson_FileName = cJSON_GetObjectItem(cjson_UploadInfo, FILENAME);
	snprintf(fileNameRaw, MAX_LEN, "%s", cJSON_Print(cjson_FileName));
	char *fileName = brewEngine_CleanupQuotes(fileNameRaw);

	/* Get the fileAbsoluteLocation */
	cJSON *cjson_FileAbsLoc = cJSON_GetObjectItem(cjson_UploadInfo, FILE_ABSOLUTE_LOCATION);
	snprintf(fileAbsLocRaw, MAX_CMD_LEN, "%s", cJSON_Print(cjson_FileAbsLoc));
	char *fileAbsLoc = brewEngine_CleanupQuotes(fileAbsLocRaw);

	/* Get the linkedAccountsJSON */
	cJSON *cjson_linkedAccountsJSON = cJSON_GetObjectItem(cjson_UploadInfo, ACCOUNTS);
	/* Append "ACS" key again with the linkedAccountsJSON array. cJSON_GetObjectItem() above extracts just the elements, however we need the full json including the "ACS" key before calling all fileHandling_ functions */
	snprintf(linkedAccountsJSON, MAX_LEN*20, "{\"%s\":%s}", ACCOUNTS, cJSON_Print(cjson_linkedAccountsJSON));

	/* Get the total number of linked accounts */
	int totalLinkedAccounts = cJSON_GetArraySize(cjson_linkedAccountsJSON);

	if(fileHandling_CreateDir(userId) == EXIT_SUCCESS)/* Create the file handling directory */
	{
		if(strncmp(split, "Y", NIBBLE_LEN) == 0)
		{
			char *brewScore = brewEngine_CalcBrewScore(linkedAccountsJSON);
			char *fileSplitState = fileHandling_SplitFile(fileAbsLoc, fileName, type, userId, brewScore);/* Perform the split and create the shreds of appropriate sizes */
			snprintf(response, MAX_LEN*10, "%s", fileSplitState);
			MEM_FREE(fileSplitState);
			MEM_FREE(brewScore);
		}
		else if(strncmp(split, "N", NIBBLE_LEN) == 0)
		{/* It's hardcoded to ZERO as of now. The JSON received should be properly validated from frontend - ideally with SPLIT set as 'N', the JSON should only contain one linked account info */
			accountName = accountHandling_GetNameFromLinkedAccounts(linkedAccountsJSON, ZERO);
			char *accountNameFmt = brewEngine_CleanupQuotes(accountName);

			/* just rename it with the account name at index 0 and move it appropriately */
			snprintf(cmd, MAX_CMD_LEN, "mv \"%s\" \"%s/%s/%s%s%s%s%d\"", fileAbsLoc, TEMP_DIR, userId, fileName, FILE_SPLIT_SEPARATOR, accountNameFmt, FILE_SPLIT_SEPARATOR, ZERO);
			system(cmd);

			snprintf(splitFileName, MAX_LEN, "%s%s%s%s%d", fileName, FILE_SPLIT_SEPARATOR, accountNameFmt, FILE_SPLIT_SEPARATOR, ZERO);
			snprintf(splitFileAbsLoc, MAX_LEN, "%s/%s/%s%s%s%s%d", TEMP_DIR, userId, fileName, FILE_SPLIT_SEPARATOR, accountNameFmt, FILE_SPLIT_SEPARATOR, ZERO);
			snprintf(fileSplitState, MAX_LEN*10, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\", \"%s\": [{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\"}]}", TYPE, type, FILENAME, fileName, UID, userId, FILE_SPLIT_STATE, ACCOUNTNAME, accountNameFmt, FILE_SPLIT_NAME, splitFileName, FILE_SPLIT_ABSOLUTE_LOCATION, splitFileAbsLoc);
			snprintf(response, MAX_LEN*10, "%s", fileSplitState);
		}

		if(strncmp(encrypted, "Y", NIBBLE_LEN) == 0)/* Perform encryption */
		{
			char *originalFileNameHash = fileHandling_GetSHA256Hash(fileAbsLoc);/* Calculate SHA 256 hash of original file */
			char *fileEncryptedState = fileHandling_EncryptShreds(fileName, type, userId, originalFileNameHash, totalLinkedAccounts); /* Encrypt each of the file shreds */
			MEM_FREE(originalFileNameHash);
			snprintf(response, MAX_LEN*10, "%s", fileEncryptedState);
			MEM_FREE(fileEncryptedState);
		}
	}
	else
	{
		snprintf(response, MAX_LEN*10, "%s", STR_FAIL);
	}

	free(cjson_UploadInfo);
	free(cjson_Type);
	free(cjson_Encrypted);
	free(cjson_Split);
	free(cjson_UserId);
	free(cjson_FileName);
	free(cjson_FileAbsLoc);
	free(cjson_linkedAccountsJSON);

	return response;
}
