
/*******************************************************
**	CloudBrew - Software Defined Distributed Public Cloud Storage	**
**	Perform file split and encryption for upload						**

**	File:		cbUpload.c										**
**	Author: 	Runcy Oommen									**
**	Date:	02/17/2016										**

**	Copyright 2016 CloudBrew Systems. All rights reserved.			**
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "cbDefines.h"
#include "fileHandling.h"
#include "MemMgr.h"
#include "brewEngine.h"
#include "accountHandling.h"
#include "cJSON.h"

/* TODO: Make changes to accept ENC and SPLT flags and perform appropriate validation and checks just like cbUpload.cpp */
int cb_upload(char *fileAbsLoc, char *fileName, char*type, char*userId, char *linkedAccountsJSON)
{
	int exit_resp = EXIT_SUCCESS;
	if(fileHandling_CreateDir(userId) == EXIT_SUCCESS)/* Create the file handling directory */
	{
		char *brewScore = brewEngine_CalcBrewScore(linkedAccountsJSON);

		fileHandling_SplitFile(fileAbsLoc, fileName, type, userId, brewScore);/* Perform the split and create the shreds of appropriate sizes */

		char *originalFileNameHash = fileHandling_GetSHA256Hash(fileAbsLoc);/* Calculate SHA 256 hash of original file */

		/* Get the total number of linked accounts */
		cJSON *cjson_linkedAccounts = cJSON_Parse(linkedAccountsJSON);
		cJSON *cjson_linkedAccountsJSON = cJSON_GetObjectItem(cjson_linkedAccounts, ACCOUNTS);
		int totalLinkedAccounts = cJSON_GetArraySize(cjson_linkedAccountsJSON);

		char *fileEncryptedState = fileHandling_EncryptShreds(fileName, type, userId, originalFileNameHash, totalLinkedAccounts);/* Encrypt each of the file shreds */

		MEM_FREE(originalFileNameHash);
		MEM_FREE(fileEncryptedState);
		MEM_FREE(brewScore);

		exit_resp = EXIT_SUCCESS;
	}
	else
		exit_resp = EXIT_FAIL;

	return exit_resp;
}

/* To be executed as ./cbUpload argv[1] argv[2] argv[3] argv[4] argv[5] */
/* argv[1] = <file_abs_loc>, argv[2] = <file_name>, argv[3] = <type>, argv[4] = <user_id>, argv[5] = <linked_accounts_json> */
/* Example: ./cbUpload '../sample_files/test.zip' 'test.zip' 'PSV' '57935cc35d664a7a13dc78dc' '{"ACS":[{"AN": "Dropbox#1_57935cc35d664a7a13dc78dc", "TS" : 6368709124, "US" : 5121223751, "MFS": 0},{"AN" : "OneDrive#1_57935cc35d664a7a13dc78dc", "TS" : 7737418240, "US" : 3368709120, "MFS": 0},{"AN" : "OneDrive#2_57935cc35d664a7a13dc78dc", "TS" : 10737418240, "US" : 5368709120, "MFS": 0},{"AN" : "GoogleDrive#1_57935cc35d664a7a13dc78dc", "TS" : 1521225472, "US" : 1068709120, "MFS": 25102789},{"AN" : "Box#1_57935cc35d664a7a13dc78dc", "TS" : 3221225472, "US" : 1368709120, "MFS": 25102789},{"AN" : "Box#2_57935cc35d664a7a13dc78dc", "TS" : 8221225356, "US" : 7268709120, "MFS": 25102789},{"AN" : "GoogleDrive#3_57935cc35d664a7a13dc78dc", "TS" : 16106127360, "US" : 4032228790, "MFS": 524288000}]}' */
int main(int argc, char *argv[])
{	
	char response[SHORT_LEN] = {'\0'};
	int exit_resp = EXIT_SUCCESS;

	if(cb_upload(argv[1], argv[2], argv[3], argv[4], argv[5]) == EXIT_SUCCESS)
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

