
/*******************************************************
**	CloudBrew - Software Defined Distributed Public Cloud Storage	**
**	Perform all tasks related to the files							**

**	File:		fileHandling.c										**
**	Author: 	Runcy Oommen									**
**	Date:	11/02/2015										**

**	Copyright 2015 CloudBrew Systems. All rights reserved.			**
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "cbDefines.h"
#include "fileHandling.h"
#include "accountHandling.h"
#include "passPhrase.h"
#include "brewEngine.h"
#include "cJSON.h"
#include "MemMgr.h"

/* Get the size of the file in bytes */
unsigned long long int fileHandling_GetSizeInBytes(char *fileAbsLoc)
{
	struct stat statBuf;
	stat(fileAbsLoc, &statBuf);
	unsigned long long int size = statBuf.st_size;
	return size;
}

/* Create the file handling directory */
int fileHandling_CreateDir(char *userId)
{
	char cmd[MAX_CMD_LEN];
	snprintf(cmd, MAX_CMD_LEN, "mkdir -p %s/%s", TEMP_DIR, userId);
	system(cmd);
	return EXIT_SUCCESS;
}

/* Get the appropriate suffix of the file shred */
char *fileHandling_GetShredSuffix(int i)
{
	switch(i)
	{
		case 1:
			return "aa";
			break;
		case 2:
			return "ab";
			break;
		case 3:
			return "ac";
			break;
		case 4:
			return "ad";
			break;
		case 5:
			return "ae";
			break;
		case 6:
			return "af";
			break;
		case 7:
			return "ag";
			break;
		case 8:
			return "ah";
			break;
		case 9:
			return "ai";
			break;
		case 10:
			return "aj";
			break;
		case 11:
			return "ak";
			break;
		case 12:
			return "al";
			break;
		case 13:
			return "am";
			break;
		case 14:
			return "an";
			break;
		case 15:
			return "ao";
			break;
		case 16:
			return "ap";
			break;
		case 17:
			return "aq";
			break;
		case 18:
			return "ar";
			break;
		case 19:
			return "as";
			break;
		case 20:
			return "at";
			break;
		case 21:
			return "au";
			break;
		case 22:
			return "av";
			break;
		case 23:
			return "aw";
			break;
		case 24:
			return "ax";
			break;
		case 25:
			return "ay";
			break;
		case 26:
			return "az";
			break;
		case 27:
			return "ba";
			break;
		case 28:
			return "bb";
			break;
		case 29:
			return "bc";
			break;
		case 30:
			return "bd";
			break;
		case 31:
			return "be";
			break;
		case 32:
			return "bf";
			break;
		case 33:
			return "bg";
			break;
		case 34:
			return "bh";
			break;
		case 35:
			return "bi";
			break;
		case 36:
			return "bj";
			break;
		case 37:
			return "bk";
			break;
		case 38:
			return "bl";
			break;
		case 39:
			return "bm";
			break;
		case 40:
			return "bn";
			break;
		case 41:
			return "bo";
			break;
		case 42:
			return "bp";
			break;
		case 43:
			return "bq";
			break;
		case 44:
			return "br";
			break;
		case 45:
			return "bs";
			break;
		case 46:
			return "bt";
			break;
		case 47:
			return "bu";
			break;
		case 48:
			return "bv";
			break;
		case 49:
			return "bw";
			break;
		case 50:
			return "bx";
			break;
		case 51:
			return "by";
			break;
		case 52:
			return "bz";
			break;
		case 53:
			return "ca";
			break;
		case 54:
			return "cb";
			break;
		case 55:
			return "cc";
			break;
		case 56:
			return "cd";
			break;
		case 57:
			return "ce";
			break;
		case 58:
			return "cf";
			break;
		case 59:
			return "cg";
			break;
		case 60:
			return "ch";
			break;
		case 61:
			return "ci";
			break;
		case 62:
			return "cj";
			break;
		case 63:
			return "ck";
			break;
		case 64:
			return "cl";
			break;
		case 65:
			return "cm";
			break;
		case 66:
			return "cn";
			break;
		case 67:
			return "co";
			break;
		case 68:
			return "cp";
			break;
		case 69:
			return "cq";
			break;
		case 70:
			return "cr";
			break;
		case 71:
			return "cs";
			break;
		case 72:
			return "ct";
			break;
		case 73:
			return "cu";
			break;
		case 74:
			return "cv";
			break;
		case 75:
			return "cw";
			break;
		case 76:
			return "cx";
			break;
		case 77:
			return "cy";
			break;
		case 78:
			return "cz";
			break;
		case 79:
			return "da";
			break;
		case 80:
			return "db";
			break;
		case 81:
			return "dc";
			break;
		case 82:
			return "dd";
			break;
		case 83:
			return "de";
			break;
		case 84:
			return "df";
			break;
		case 85:
			return "dg";
			break;
		case 86:
			return "dh";
			break;
		case 87:
			return "di";
			break;
		case 88:
			return "dj";
			break;
		case 89:
			return "dk";
			break;
		case 90:
			return "dl";
			break;
		case 91:
			return "dm";
			break;
		case 92:
			return "dn";
			break;
		case 93:
			return "do";
			break;
		case 94:
			return "dp";
			break;
		case 95:
			return "dq";
			break;
		case 96:
			return "dr";
			break;
		case 97:
			return "ds";
			break;
		case 98:
			return "dt";
			break;
		case 99:
			return "du";
			break;
		case 100:
			return "dv";
			break;
	}
	return "zz"; /* Should not reach here */
}

/* Get the SHA256 hash */
char *fileHandling_GetSHA256Hash(char *fileAbsLoc)
{
	char cmd[MAX_CMD_LEN*2] = {'\0'};
	FILE *fp;
	struct stat statBuf;
	char *encryptedFileNameHash = MEM_XMALLOC(MAX_LEN);
	
	snprintf(cmd, MAX_CMD_LEN*2, "sha256sum \"%s\" | awk {'print $1'} > %s", fileAbsLoc, TEMP_ENCRYPTED_FILENAMEHASH);
	system(cmd);

	if(stat(TEMP_ENCRYPTED_FILENAMEHASH, &statBuf) == 0)
	{
		fp = fopen(TEMP_ENCRYPTED_FILENAMEHASH, "r");
		if(fp)
		{
			if (fgets(encryptedFileNameHash, MAX_LEN, fp) != NULL)
				strtok(encryptedFileNameHash, "\n");/* Remove new line from end */
		}
		fclose(fp);
	}

	snprintf(cmd, MAX_CMD_LEN*2, "rm -f %s", TEMP_ENCRYPTED_FILENAMEHASH);
	system(cmd);

	return encryptedFileNameHash;
}

/* Delete the file shreds that were created */
int fileHandling_DeleteShreds(char *splitFileName, char *userId)
{
	char cmd[MAX_CMD_LEN*2] = {'\0'};
	snprintf(cmd, MAX_CMD_LEN*2, "rm -f \"%s/%s/%s\"", TEMP_DIR, userId, splitFileName);
	system(cmd);
	return EXIT_SUCCESS;
}

/* Encrypt the file shreds */
char *fileHandling_EncryptShreds(char *fileName, char *type, char *userId, char *originalFileNameHash, int totalLinkedAccounts)
{
	char cmd[MAX_CMD_LEN*2] = {'\0'}, passPhrase[MAX_LEN+1] = {'\0'}, fileEncryptedStateJSON[MAX_LEN*10] = {'\0'}, fileEncryptedStateJSONSingle[MAX_LEN*2] = {'\0'}, accountNameCopy[MAX_LEN] = {'\0'};
	FILE *fp;
	char *accountName, *shredFileName_chopped, *shredFileNameAccountName_chopped, *shredFileNameAccountIndex_chopped;
	char *fileEncryptedState = MEM_MALLOC(MAX_LEN*10);
	char *shredFileName = MEM_MALLOC(MAX_LEN);
	char *shredFileNameAccountName = MEM_MALLOC(MAX_LEN);
	char *shredFileNameAccountIndex = MEM_MALLOC(MAX_LEN);
	int len, ctr=0;

	snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; find . -name \"%s*\" > %s", TEMP_DIR, userId, fileName, TEMP_SHRED_FILESLIST);/* Get a list of all the file shreds */
	system(cmd);

	fp = fopen(TEMP_SHRED_FILESLIST, "r");
	if(fp)
	{
		snprintf(fileEncryptedStateJSON, MAX_LEN*10, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\", \"%s\": [", TYPE, type, FILENAME, fileName, UID, userId, FILE_SPLIT_ENCRYPTED_STATE);
		while(fgets(shredFileName, MAX_LEN, fp) != NULL)/* Read the file list till EOF */
		{
			/* Remove new line from end and "./" from the file name that gets added as prefix from the search */
			strtok(shredFileName, "\n");
			shredFileName_chopped = shredFileName + 2;

			/* Save two copies to determine account name and index */
			snprintf(shredFileNameAccountName, MAX_LEN, "%s", shredFileName_chopped);
			snprintf(shredFileNameAccountIndex, MAX_LEN, "%s", shredFileName_chopped);

			/* Get account name from shred file name */
			len = strlen(fileName) + strlen(FILE_SPLIT_SEPARATOR);
			shredFileNameAccountName_chopped = shredFileNameAccountName + len;
			accountName = strtok(shredFileNameAccountName_chopped, FILE_SPLIT_SEPARATOR);

			/* Get index from shred file name */
			len = strlen(fileName) + strlen(FILE_SPLIT_SEPARATOR) + strlen(accountName) + strlen(FILE_SPLIT_SEPARATOR);
			shredFileNameAccountIndex_chopped = shredFileNameAccountIndex + len;

			snprintf(accountNameCopy, MAX_LEN, "%s", accountName);
			char *accountNameCleanupHash = brewEngine_CleanupHash(accountNameCopy);

			if(strncmp(ACCOUNT_GOOGLEDRIVE, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_GOOGLEDRIVE);
			else if(strncmp(ACCOUNT_ONEDRIVE, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_ONEDRIVE);
			else if(strncmp(ACCOUNT_BOX, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_BOX);
			else if(strncmp(ACCOUNT_DROPBOX, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_DROPBOX);

			char encryptedFileName[MAX_LEN] = {'\0'};
			snprintf(encryptedFileName, MAX_LEN, "%s%s%s%s%d", fileName, FILE_ENCRYPT_SEPARATOR, accountName, FILE_ENCRYPT_SEPARATOR, atoi(shredFileNameAccountIndex_chopped));

			snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; echo \"%s\" | gpg --batch --passphrase-fd 0 --output \"%s\" --symmetric --cipher-algo %s \"%s\""QUIETLY, TEMP_DIR, userId, passPhrase, encryptedFileName, CB_DEFAULT_CIPHER, shredFileName_chopped);
			system(cmd);

			/* Delete the leftover original split file shreds */
			fileHandling_DeleteShreds(shredFileName_chopped, userId);

			/* Get the SHA256 hash of the encrypted split file shreds */
			char encryptedFileAbsLoc[MAX_LEN] = {'\0'};
			snprintf(encryptedFileAbsLoc, MAX_LEN, "%s/%s/%s", TEMP_DIR, userId, encryptedFileName);
			fileHandling_GetSHA256Hash(encryptedFileAbsLoc);

			snprintf(fileEncryptedStateJSONSingle, MAX_LEN*2, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\"}", ACCOUNTNAME, accountName, ENCRYPTED_SPLIT_NAME, encryptedFileName, ENCRYPTED_ABSOLUTE_LOCATION, encryptedFileAbsLoc);
			strcat(fileEncryptedStateJSON, fileEncryptedStateJSONSingle);

			if((ctr == (FILE_SPLIT_MAX-1)) || (totalLinkedAccounts == SINGLE_LINKED_ACCOUNT)) /* Check if it's the last split or if there's just one linked account - craft json accordingly */
				strcat(fileEncryptedStateJSON, "]}");
			else
				strcat(fileEncryptedStateJSON, ",");

			ctr++;
		}
		MEM_FREE(shredFileName);
		MEM_FREE(shredFileNameAccountName);
		MEM_FREE(shredFileNameAccountIndex);

		snprintf(fileEncryptedState, MAX_LEN*10, "%s", fileEncryptedStateJSON);
	}
	else
		snprintf(fileEncryptedState, MAX_LEN*10, "%s", STR_FAIL);

	fclose(fp);
	snprintf(cmd, MAX_CMD_LEN*2, "rm -f %s", TEMP_SHRED_FILESLIST);
	system(cmd);

	//printf("Encryption successful for the file shreds %s\n", fileName);
	/* At the end of the encryption, the resultant encrypted split file name should be in the format <File_Name>.<Account_Name>.<AccountIndex_Of_BrewScore> */
	return fileEncryptedState;
}

/* Decrypt the file shreds */
char *fileHandling_DecryptShreds(char *fileName, char *userId, char *type)
{
	char cmd[MAX_CMD_LEN*2] = {'\0'}, passPhrase[MAX_LEN+1] = {'\0'}, fileAbsLoc[MAX_LEN] = {'\0'}, accountName[MAX_LEN] = {'\0'};
	char encryptedFileNameRawCopy[MAX_LEN] = {'\0'}, fileDecryptedStateJSON[MAX_LEN*10] = {'\0'}, fileDecryptedStateJSONSingle[MAX_LEN*2] = {'\0'};
	FILE *fp;
	int ctr = 0;
	char *encryptedFileNameRaw = MEM_XMALLOC(MAX_LEN);
	char *encryptedFileCount = MEM_XMALLOC(NIBBLE_LEN);
	char *encryptedFileNameSuffix = MEM_XMALLOC(MAX_LEN);
	char *encryptedFileNameRaw_chopped, *encryptedFileNameSuffix_chopped;

	/* Check if whole file exist (possibly from earlier download/join operation)? If yes, delete it first */
	/* Ideally, this should not happen, since we move the joined file from the temp loc while presenting it for download. This is like a double-check to prevent segfault */
	struct stat fileBuf;
	snprintf(fileAbsLoc, MAX_LEN, "%s/%s/%s", TEMP_DIR, userId, fileName);
	if(stat(fileAbsLoc, &fileBuf) == 0)
	{
		/* TODO: Validate the checksum of the existing file from SQLite and skip below decryption process instead of deletion. */
		/* However, before proceeding check if such a scenario (of original file already existing) would really exist in production env as we move/delete the file while presenting for download */
		fileHandling_DeleteShreds(fileName, userId);
	}

	snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; find . -name \"%s*\" | wc -l > %s", TEMP_DIR, userId, fileName, TEMP_ENCRYPTED_COUNT); /* Get the count of all the encrypted file shreds */
	system(cmd);
	fp = fopen(TEMP_ENCRYPTED_COUNT, "r");
	if(fp)
	{
		fgets(encryptedFileCount, NIBBLE_LEN, fp);
		strtok(encryptedFileCount, "\n");/* Remove new line from end */
		fclose(fp);
	}
	snprintf(cmd, MAX_CMD_LEN*2, "rm -f %s", TEMP_ENCRYPTED_COUNT);
	system(cmd);

	sprintf(cmd, "cd %s/%s; find . -name \"%s*\" > %s", TEMP_DIR, userId, fileName, TEMP_ENCRYPTED_FILESLIST); /* Get a list of all the encrypted file shreds */
	system(cmd);
	fp = fopen(TEMP_ENCRYPTED_FILESLIST, "r");
	if(fp)
	{
		snprintf(fileDecryptedStateJSON, MAX_LEN*10, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\", \"%s\": [", TYPE, type, FILENAME, fileName, UID, userId, FILE_DECRYPTED_STATE);
		while(fgets(encryptedFileNameRaw, MAX_LEN, fp) != NULL)/* Read the file list till EOF */
		{
			/* Remove new line from end and "./" from the file name that gets added as prefix from the search */
			strtok(encryptedFileNameRaw, "\n");
			encryptedFileNameRaw_chopped = encryptedFileNameRaw + 2;
			snprintf(encryptedFileNameRawCopy, MAX_LEN, "%s", encryptedFileNameRaw_chopped);

			/* Get encrypted file name suffix */
			snprintf(encryptedFileNameSuffix, MAX_LEN, "%s", encryptedFileNameRaw_chopped);
			encryptedFileNameSuffix_chopped = encryptedFileNameSuffix + strlen(fileName) + strlen(FILE_ENCRYPT_SEPARATOR);

			/* Read the account name to get it's corresponding passphrase for encryption of each of the file shreds */
			char *accountNameRaw = strtok(encryptedFileNameSuffix_chopped, FILE_ENCRYPT_SEPARATOR);
			snprintf(accountName, MAX_LEN, "%s", accountNameRaw);
			char *accountIndex = strtok(NULL, FILE_ENCRYPT_SEPARATOR);
			char *accountNameCleanupID = brewEngine_CleanupID(accountName);
			char *accountNameCleanupHash = brewEngine_CleanupHash(accountNameCleanupID);

			if(strncmp(ACCOUNT_GOOGLEDRIVE, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_GOOGLEDRIVE);
			else if(strncmp(ACCOUNT_ONEDRIVE, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_ONEDRIVE);
			else if(strncmp(ACCOUNT_BOX, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_BOX);
			else if(strncmp(ACCOUNT_DROPBOX, accountNameCleanupHash, MAX_LEN) == 0)
				snprintf(passPhrase, MAX_LEN+1, "%s", PASSPHRASE_DROPBOX);

			/* Decrypt the encrypted split file shreds */
			/* Make sure GPG version is 2.0+ */
			snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; echo \"%s\" | gpg --batch --passphrase-fd 0 --output \"%s%s%d\" --decrypt \"%s\""QUIETLY, TEMP_DIR, userId, passPhrase, fileName, DOT, atoi(accountIndex), encryptedFileNameRawCopy);
			system(cmd);

			snprintf(fileDecryptedStateJSONSingle, MAX_LEN*2, "\"%s\": \"%s%s%d\"}", FILE_DECRYPTED_NAME, fileName, DOT, atoi(accountIndex));
			strcat(fileDecryptedStateJSON, fileDecryptedStateJSONSingle);

			/* Delete the leftover encrypted split file shreds */
			fileHandling_DeleteShreds(encryptedFileNameRawCopy, userId);

			if(ctr == (atoi(encryptedFileCount)-1)) /* Check if it's the last split and also craft json accordingly */
				strcat(fileDecryptedStateJSON, "]}");
			else
				strcat(fileDecryptedStateJSON, ",");

			ctr++;
		}
		fclose(fp);
	}
	sprintf(cmd, "rm -f %s", TEMP_ENCRYPTED_FILESLIST);
	system(cmd);

	char *fileDecryptedState = MEM_XMALLOC(MAX_LEN*10);
	snprintf(fileDecryptedState, MAX_LEN*10, "%s", fileDecryptedStateJSON);

	//printf("Decryption successful for the file shreds %s\n", fileName);
	MEM_FREE(encryptedFileNameRaw);
	MEM_FREE(encryptedFileNameSuffix);
	MEM_FREE(encryptedFileCount);

	return fileDecryptedState;
}

/* Join the file shreds to create the required output file */
char *fileHandling_JoinShreds(char *fileName, char *type, char *userId)
{
	char cmd[MAX_CMD_LEN] = {'\0'}, shredFileNameTemp[MAX_LEN] = {'\0'};
	char *fileDecryptedState = MEM_MALLOC(MAX_LEN*5), *shredFileNameRaw = MEM_XMALLOC(MAX_LEN), *shredFileCount = MEM_XMALLOC(NIBBLE_LEN);
	char *shredFileNameRaw_chopped;
	FILE *fp;
	int ctr=0, len;

	/* Get a list of all the file shreds participating in the join operation */
	snprintf(cmd, MAX_CMD_LEN, "cd %s/%s; find . -name \"%s*\" > %s", TEMP_DIR, userId, fileName, TEMP_JOIN_FILELIST);
	system(cmd);

	/* Get the count of all the file shreds */
	snprintf(cmd, MAX_CMD_LEN, "cd %s/%s; find . -name \"%s*\" | wc -l > %s", TEMP_DIR, userId, fileName, TEMP_JOIN_COUNT);
	system(cmd);

	fp = fopen(TEMP_JOIN_COUNT, "r");
	if(fp)
	{
		fgets(shredFileCount, NIBBLE_LEN, fp);
		fclose(fp);
	}

	fp = fopen(TEMP_JOIN_FILELIST, "r");
	if(fp)
	{
		while(fgets(shredFileNameRaw, MAX_LEN, fp) != NULL)/* Read the join file list till EOF */
		{
			strtok(shredFileNameRaw, "\n");/* Remove new line from end */
			len = strlen(shredFileNameRaw);
			shredFileNameRaw_chopped = shredFileNameRaw + (len-1);/* Get the shred file prefix */
			/* What we're doing below is renaming the shred file name with the same prefix for join operation */
			snprintf(cmd, MAX_CMD_LEN, "cd %s/%s; mv \"%s\" \"%s%s%d\"", TEMP_DIR, userId, shredFileNameRaw, fileName, DOT, atoi(shredFileNameRaw_chopped));
			system(cmd);
		}
		for(ctr=0; ctr<atoi(shredFileCount); ctr++)
		{
			/* We know the count of shreds. So lets iterate and start "cat" operation in the same order from 0 to n-1 */
			snprintf(cmd, MAX_CMD_LEN, "cd %s/%s; cat \"%s%s%d\" >> \"%s\"", TEMP_DIR, userId, fileName, DOT, ctr, fileName);
			system(cmd);
			/* Delete the leftover decrypted split file shreds */
			snprintf(shredFileNameTemp, MAX_LEN, "%s%s%d", fileName, DOT, ctr);
			fileHandling_DeleteShreds(shredFileNameTemp, userId);
		}
		fclose(fp);
	}

	snprintf(cmd, MAX_CMD_LEN, "rm -f %s", TEMP_JOIN_FILELIST);
	system(cmd);
	snprintf(cmd, MAX_CMD_LEN, "rm -f %s", TEMP_JOIN_COUNT);
	system(cmd);

	snprintf(fileDecryptedState, MAX_LEN*5, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\", \"%s\": {\"%s\": \"%s/%s/%s\"}}", TYPE, type, FILENAME, fileName, UID, userId, FILE_DECRYPTED_JOINED_STATE, FILE_ABSOLUTE_LOCATION, TEMP_DIR, userId,fileName);

	//printf("Joining successful for the file shreds to create %s\n", fileName);
	MEM_FREE(shredFileNameRaw);
	MEM_FREE(shredFileCount);
	return fileDecryptedState;
}

/* Splits the file based on the specified brewscore */
char *fileHandling_SplitFile(char *fileAbsLoc, char *fileName, char *type, char *userId, char *brewScore)
{
	int ctrParticipationAccount, ctrCombinedAccountPercent;
	int initRootFile = 2, initRootFileCopy = 2, initSeedFile=3, combinedAccountPercent = 0, initFirstFile = 1, initSecondFile = 2, thirdFile = 3;
	char splitFileName[MAX_LEN] = {'\0'}, cmd[MAX_CMD_LEN*2] = {'\0'}, fileSplitStateJSON[MAX_LEN*10] = {'\0'}, fileSplitStateJSONSingle[MAX_LEN*2] = {'\0'}, weightedSplitFileName[MAX_LEN] = {'\0'}, weightedSplitFileAbsLoc[MAX_LEN] = {'\0'};
	char *perAccountName, *perAccountPercent, *perAccountNameFmt;

	/* Get the file size in bytes */
	unsigned long long int fileTotalSize = fileHandling_GetSizeInBytes(fileAbsLoc);

	/* Split it into a hundred parts initially */
	unsigned long long int splitSizePerAccount = fileTotalSize / HUNDRED_PARTS;
	unsigned long long int splitSizeRemainder = fileTotalSize % HUNDRED_PARTS;

	if(splitSizeRemainder != 0) /* If a perfect division has not happened, add the split size remainder to the original split size so that there are no left-out ghost files of negligible size */
		splitSizePerAccount += splitSizeRemainder;

	/* Splits the file on filesize (in bytes) into /tmp/upload/<userId> with the original file name as prefix */
	snprintf(cmd, MAX_CMD_LEN*2, "split -b %llu \"%s\" \"%s/%s/%s\"", splitSizePerAccount, fileAbsLoc, TEMP_DIR, userId, fileName);
	system(cmd);

	/* Get the number of accounts that are participating for this split from the brewscore */
	cJSON *jsonBrewScoreRaw = cJSON_Parse(brewScore);
	cJSON *jsonBrewScore = cJSON_GetObjectItem(jsonBrewScoreRaw, BREWSCORE);
	int totalParticipationAccount = cJSON_GetArraySize(jsonBrewScore);

	snprintf(fileSplitStateJSON, MAX_LEN*10, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\", \"%s\": [", TYPE, type, FILENAME, fileName, UID, userId, FILE_SPLIT_STATE);
	for(ctrParticipationAccount=0;ctrParticipationAccount<totalParticipationAccount;ctrParticipationAccount++)
	{
		/* Retireve the percentage value and account name of the linked account from it's brewscore */
		perAccountPercent = accountHandling_GetPercentFromBrewScore(brewScore, ctrParticipationAccount);
		perAccountName = accountHandling_GetNameFromBrewScore(brewScore, ctrParticipationAccount);

		if(ctrParticipationAccount < totalParticipationAccount)
		{
			/* Create the first root file for the relevant account percentage that's being picked-up */
			snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; cat \"%s%s\" \"%s%s\" > \"%s%d\"", TEMP_DIR, userId, fileName, fileHandling_GetShredSuffix(initFirstFile), fileName, fileHandling_GetShredSuffix(initSecondFile), fileName, initRootFile);
			system(cmd);

			/* Delete the first and second split file shreds of the account that being executed */
			snprintf(splitFileName, MAX_LEN, "%s%s", fileName, fileHandling_GetShredSuffix(initFirstFile));
			fileHandling_DeleteShreds(splitFileName, userId);
			snprintf(splitFileName, MAX_LEN, "%s%s", fileName, fileHandling_GetShredSuffix(initSecondFile));
			fileHandling_DeleteShreds(splitFileName, userId);

			combinedAccountPercent = combinedAccountPercent + atoi(perAccountPercent);
			for(ctrCombinedAccountPercent=thirdFile;ctrCombinedAccountPercent<=combinedAccountPercent;ctrCombinedAccountPercent++)
			{
				/* The first iteration here will use the root file created above everytime to create the seed of this loop. */
				/* This seed will then create subsequent bigger files by joining with the next one in queue */
				snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; cat \"%s%d\" \"%s%s\" > \"%s%d\"", TEMP_DIR, userId, fileName, initRootFileCopy, fileName, fileHandling_GetShredSuffix(ctrCombinedAccountPercent), fileName, initSeedFile);
				system(cmd);

				/* Delete the smaller shreds thats no longer required now after each iteration */
				snprintf(splitFileName, MAX_LEN, "%s%d", fileName, initRootFileCopy);
				fileHandling_DeleteShreds(splitFileName, userId);
				snprintf(splitFileName, MAX_LEN, "%s%s", fileName, fileHandling_GetShredSuffix(ctrCombinedAccountPercent));
				fileHandling_DeleteShreds(splitFileName, userId);
				initRootFileCopy++;
				initSeedFile++;

				/* Perform required initializations when it's reached the account percentage depending on the brew score */ 
				if(ctrCombinedAccountPercent == combinedAccountPercent)
				{
					/* Also change the final resultant split file suffixed with the index of account name as present in the brew score */
					snprintf(cmd, MAX_CMD_LEN*2, "cd %s/%s; mv \"%s%d\" \"%s%s%s%s%d\"", TEMP_DIR, userId, fileName, ctrCombinedAccountPercent, fileName, FILE_SPLIT_SEPARATOR, perAccountName, FILE_SPLIT_SEPARATOR, ctrParticipationAccount);
					system(cmd);

					perAccountNameFmt = brewEngine_CleanupQuotes(perAccountName);

					snprintf(weightedSplitFileName, MAX_LEN, "%s%s%s%s%d", fileName, FILE_SPLIT_SEPARATOR, perAccountNameFmt, FILE_SPLIT_SEPARATOR, ctrParticipationAccount);
					snprintf(weightedSplitFileAbsLoc, MAX_LEN, "%s/%s/%s", TEMP_DIR, userId, weightedSplitFileName);

					snprintf(fileSplitStateJSONSingle, MAX_LEN*2, "{\"%s\": \"%s\", \"%s\": \"%s\", \"%s\": \"%s\"}", ACCOUNTNAME, perAccountNameFmt, FILE_SPLIT_NAME, weightedSplitFileName, FILE_SPLIT_ABSOLUTE_LOCATION, weightedSplitFileAbsLoc);
					strcat(fileSplitStateJSON, fileSplitStateJSONSingle);

					initFirstFile = initSeedFile;
					initSecondFile = initFirstFile + 1;
					thirdFile = initSecondFile + 1;
					initRootFile = initSeedFile;
					initRootFile++;
					initRootFileCopy = initRootFile;
					initSeedFile = initRootFile+1;
				}
			}

			if(ctrParticipationAccount == (totalParticipationAccount-1)) /* Check if it's the last split and also craft json accordingly */
				strcat(fileSplitStateJSON, "]}");
			else
				strcat(fileSplitStateJSON, ",");
		}
	}

	char *fileSplitState = MEM_XMALLOC(MAX_LEN*10);
	snprintf(fileSplitState, MAX_LEN*10, "%s", fileSplitStateJSON);

	free(jsonBrewScoreRaw);
	free(jsonBrewScore);
	MEM_FREE(perAccountName);
	MEM_FREE(perAccountPercent);

	//printf("Splitting successful for the file %s\n", fileName);
	/* At the end of the split, the resultant split file name should be in the format <File_Name>??<Account_Name>??<AccountIndex_Of_BrewScore> */
	return fileSplitState;
}

/* TODO: work on ensuring that the file permissions are same as before for a file - as of now I see that the permissions are changed after all processes are done, this should not be the case */

