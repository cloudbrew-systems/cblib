
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

#include "cbDefines.h"
#include "fileHandling.h"
#include "MemMgr.h"

int cb_download(char *fileName, char *type, char*userId)
{
	int exit_resp = EXIT_SUCCESS;
	if(fileHandling_CreateDir(userId) == EXIT_SUCCESS)/* Create the file handling directory */
	{
		char *fileDecryptedState = fileHandling_DecryptShreds(fileName, userId, type);
		char *fileJoinedState = fileHandling_JoinShreds(fileName, type, userId);/* Join it all together in the right order to create the original file */
		MEM_FREE(fileJoinedState);
		MEM_FREE(fileDecryptedState);
		exit_resp = EXIT_SUCCESS;
	}
	else
		exit_resp = EXIT_FAIL;

	return exit_resp;
}

/* To be executed as ./cbDownload argv[1] argv[2] argv[3] */
/* argv[1] = <file_name>, argv[2] = <type>, argv[3] = <user_id> */
/* Example: ./cbDownload 'test.zip' 'PSV' '1001' */
int main(int argc, char *argv[])
{
	char response[SHORT_LEN] = {'\0'};
	int exit_resp = EXIT_SUCCESS;

	if(cb_download(argv[1], argv[2], argv[3]) == EXIT_SUCCESS)
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
