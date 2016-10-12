
/*******************************************************
**	CloudBrew - Software Defined Distributed Public Cloud Storage	**
**	Entry point for all tasks in the backend/server					**

**	File:		cloudbrew.c										**
**	Author: 	Runcy Oommen									**
**	Date:	11/12/2015										**

**	Copyright 2015 CloudBrew Systems. All rights reserved.			**
*******************************************************/

/* The usage of this file is now deprecated. It's now split as cbpload.c and cbDownload.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cbDefines.h"
#include "accountHandling.h"
#include "fileHandling.h"
#include "cbLog.h"
#include "MemMgr.h"
#include "brewEngine.h"
#include "cJSON.h"

/* TODO: Make changes to accept ENC and SPLT flags and perform appropriate validation and checks just like cbUpload.cpp and cbDownload.cpp */
int cb_updown(char *fileAbsLoc, char *fileName, char*type, char*userId, char *linkedAccountsJSON)
{
	int exit_resp = EXIT_SUCCESS;
	if(fileHandling_CreateDir(userId) == EXIT_SUCCESS)
	{
		char *brewScore = brewEngine_CalcBrewScore(linkedAccountsJSON);

		fileHandling_SplitFile(fileAbsLoc, fileName, type, userId, brewScore);/* Perform the split and create the shreds of appropriate sizes */

		char *originalFileNameHash = fileHandling_GetSHA256Hash(fileAbsLoc);/* Calculate SHA 256 hash of original file */

		/* Get the total number of linked accounts */
		cJSON *cjson_linkedAccounts = cJSON_Parse(linkedAccountsJSON);
		cJSON *cjson_linkedAccountsJSON = cJSON_GetObjectItem(cjson_linkedAccounts, ACCOUNTS);
		int totalLinkedAccounts = cJSON_GetArraySize(cjson_linkedAccountsJSON);

		char *fileEncryptedState = fileHandling_EncryptShreds(fileName, type, userId, originalFileNameHash, totalLinkedAccounts);/* Encrypt each of the file shreds */
		char *fileDecryptedState = fileHandling_DecryptShreds(fileName, userId, type);
		char *fileJoinedState = fileHandling_JoinShreds(fileName, type, userId);

		MEM_FREE(brewScore);
		MEM_FREE(fileEncryptedState);
		MEM_FREE(originalFileNameHash);
		MEM_FREE(fileDecryptedState);
		MEM_FREE(fileJoinedState);
		exit_resp = EXIT_SUCCESS;
	}
	else
		exit_resp = EXIT_FAIL;

	return exit_resp;
}

/* To be executed as ./cloudbrew argv[1] argv[2] argv[3] argv[4] argv[5] */
/* argv[1] = <file_abs_loc>, argv[2] = <file_name>, argv[3] = <type>, argv[4] = <user_id>, argv[5] = <linked_accounts_json> */
/* Example: ./cloudbrew '../sample_files/test.zip' 'test.zip' 'PSV' '1001' '{"ACS":[{"AN":"GoogleDrive","TS":16106127360,"US":6442450944,"MFS":0},{"AN":"Dropbox","TS":10737418240,"US":5368709120,"MFS":2510234}]}' */
int main(int argc, char *argv[])
{
	char response[SHORT_LEN] = {'\0'};
	int exit_resp = EXIT_SUCCESS;

	if(cb_updown(argv[1], argv[2], argv[3], argv[4], argv[5]) == EXIT_SUCCESS)
	{
		snprintf(response, SHORT_LEN, "%s", "{\"success\": \"0\"}");
		exit_resp = EXIT_SUCCESS;
	}
	else
	{
		snprintf(response, SHORT_LEN, "%s", "{\"fail\": \"1\"}");
		exit_resp = EXIT_FAIL;
	}

	printf("%s\n", response);
	return exit_resp;
}

