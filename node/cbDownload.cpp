
/*******************************************************
**	CloudBrew - Software Defined Distributed Public Cloud Storage	**
**	Perform file decryption and join for download					**

**	File:		cbDownload.c										**
**	Author: 	Runcy Oommen									**
**	Date:	02/17/2016										**

**	Copyright 2016 CloudBrew Systems. All rights reserved.			**
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbDownload.h"
#include "cbDefines.h"
#include "fileHandling.h"
#include "cJSON.h"
#include "accountHandling.h"
#include "fileHandling.h"
#include "brewEngine.h"
#include "MemMgr.h"

/* Imp Note (06/27/2016): Don't get mistaken by the extension of .cpp. This is essentially a .c file with prettymuch straight forward C code renamed as .cpp to compile with node-gyp for creating the node module */

char *cb_download(char *downloadInfo)
{
	char *response = (char *)MEM_XMALLOC(MAX_LEN*5);
	char typeRaw[BYTE_LEN] = {'\0'}, userIdRaw[SHORT_LEN] = {'\0'}, fileNameRaw[MAX_LEN] = {'\0'}, encryptedRaw[NIBBLE_LEN] = {'\0'}, splitRaw[NIBBLE_LEN] = {'\0'};

	cJSON *cjson_DownloadInfo = cJSON_Parse(downloadInfo);

	/* Get the type */
	cJSON *cjson_Type = cJSON_GetObjectItem(cjson_DownloadInfo, TYPE);
	snprintf(typeRaw, BYTE_LEN, "%s", cJSON_Print(cjson_Type));
	char *type = brewEngine_CleanupQuotes(typeRaw);

	/* Get the encrypted flag */
	cJSON *cjson_Encrypted = cJSON_GetObjectItem(cjson_DownloadInfo, ENCRYPTED);
	snprintf(encryptedRaw, NIBBLE_LEN, "%s", cJSON_Print(cjson_Encrypted));
	char *encrypted = brewEngine_CleanupQuotes(encryptedRaw);

	/* Get the split flag */
	cJSON *cjson_Split = cJSON_GetObjectItem(cjson_DownloadInfo, SPLIT);
	snprintf(splitRaw, NIBBLE_LEN, "%s", cJSON_Print(cjson_Split));
	//char *split = brewEngine_CleanupQuotes(splitRaw);
	brewEngine_CleanupQuotes(splitRaw);

	/* Get the userId */
	cJSON *cjson_UserId = cJSON_GetObjectItem(cjson_DownloadInfo, UID);
	snprintf(userIdRaw, SHORT_LEN, "%s", cJSON_Print(cjson_UserId));
	char *userId = brewEngine_CleanupQuotes(userIdRaw);

	/* Get the fileName */
	cJSON *cjson_FileName = cJSON_GetObjectItem(cjson_DownloadInfo, FILENAME);
	snprintf(fileNameRaw, MAX_LEN, "%s", cJSON_Print(cjson_FileName));
	char *fileName = brewEngine_CleanupQuotes(fileNameRaw);

	if(fileHandling_CreateDir(userId) == EXIT_SUCCESS)/* Create the file handling directory */
	{
		if(strncmp(encrypted, "Y", NIBBLE_LEN) == 0)
		{
			char *fileDecryptedState = fileHandling_DecryptShreds(fileName, userId, type);
			char *fileJoinedState = fileHandling_JoinShreds(fileName, type, userId);/* Join it all together in the right order to create the original file */
			snprintf(response, MAX_LEN*5, fileJoinedState);
			MEM_FREE(fileJoinedState);
			MEM_FREE(fileDecryptedState);
		}
		else
		{
			char *fileJoinedState = fileHandling_JoinShreds(fileName, type, userId);/* Join it all together in the right order to create the original file */
			snprintf(response, MAX_LEN*5, fileJoinedState);
			MEM_FREE(fileJoinedState);
		}
	}
	else
		snprintf(response, MAX_LEN*5, STR_FAIL);

	free(cjson_DownloadInfo);
	free(cjson_Type);
	free(cjson_UserId);
	free(cjson_FileName);
	return response;
}

