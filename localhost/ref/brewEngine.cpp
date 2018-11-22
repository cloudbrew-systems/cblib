/*
CloudBrew - Software Defined Distributed Public Cloud Storage
Heart of the system where the real magic happens

File:	brewEngine.cpp
Author: Runcy Oommen
Date:	12/13/2015

Copyright 2015 CloudBrew Systems. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cbDefines.h"
#include "brewEngine.h"
#include "accountHandling.h"
#include "MemMgr.h"
#include "fileHandling.h"

char* brewEngine_CleanupQuotes(char *accountName)
{
	accountName++;
	strtok(accountName, "\"");
	return accountName;
}

char* brewEngine_CleanupID(char *accountName)
{
	strtok(accountName, "_");
	return accountName;
}

char* brewEngine_CleanupHash(char *accountName)
{
	strtok(accountName, "#");
	return accountName;
}

char *brewEngine_GetPerAccountName(int index, cJSON *cjson_AccountsTotal)
{
	char *accountNameFmt;
	char accountName[SHORT_LEN] = {'\0'};

	cJSON *cjson_Account = cJSON_GetArrayItem(cjson_AccountsTotal, index);

	cJSON *cjson_AccountName = cJSON_GetObjectItem(cjson_Account, ACCOUNTNAME);
	snprintf(accountName, SHORT_LEN, "%s", cJSON_Print(cjson_AccountName));
	accountNameFmt = brewEngine_CleanupQuotes(accountName);

	return accountNameFmt;
}

double brewEngine_GetPerAccountFreeSpaceStats(int ctr, int index, cJSON *cjson_AccountsTotal, double totalAccountFreeSpace, int totalAccountFreeSpacePercent)
{
	double perAccountTotalSpace = 0, perAccountUsedSpace = 0, perAccountFreeSpace = 0, perAccountFreeSpaceStat = 0;
	char totalSpace[SHORT_LEN] = {'\0'}, usedSpace[SHORT_LEN] = {'\0'};
	int perAccountFreeSpacePercent = 0, diffFromHundred = 0;

	cJSON *cjson_Account = cJSON_GetArrayItem(cjson_AccountsTotal, index);

	/* Get total space */
	cJSON *cjson_TotalSpace = cJSON_GetObjectItem(cjson_Account, TOTALSPACE);
	snprintf(totalSpace, SHORT_LEN, "%s", cJSON_Print(cjson_TotalSpace));
	perAccountTotalSpace = atof(totalSpace);

	/* Get used space */
	cJSON *cjson_UsedSpace = cJSON_GetObjectItem(cjson_Account, USEDSPACE);
	snprintf(usedSpace, SHORT_LEN, "%s", cJSON_Print(cjson_UsedSpace));
	perAccountUsedSpace = atof(usedSpace);

	/* Now calculate the free space */
	perAccountFreeSpace = perAccountTotalSpace - perAccountUsedSpace;

	if((totalAccountFreeSpace == TOTAL_ACS_FS_NOTCALC) && (totalAccountFreeSpacePercent == TOTAL_ACS_FS_PERCENT_NOTCALC))
	/* Calculate "Per Account FreeSpace" */
	{
		perAccountFreeSpaceStat = perAccountFreeSpace;
	}
	else
	/* Calculate "Per Account FreeSpace Percent" */
	{
		perAccountFreeSpacePercent = (perAccountFreeSpace/totalAccountFreeSpace)*100; /* Get the per account percentage */

		/* Add this to totalAccountFreeSpacePercent for final tally perspective. It should total to 100 for the final iteration when this method is typically called from a loop  */
		totalAccountFreeSpacePercent = totalAccountFreeSpacePercent + perAccountFreeSpacePercent;

		/* The below block executed only if it's the last iteration */
		int totalLinkedAccounts = cJSON_GetArraySize(cjson_AccountsTotal);
		if(totalLinkedAccounts > FILE_SPLIT_MAX)/* More linked accounts than max file splits allowed? */
		{
			/* If it's the last iteration, total account percentage should be 100 by the time we reach here.
			If not 100 already, round-off accordingly with the perAccountFreeSpacePercent of the last iteration */
			if((FILE_SPLIT_MAX-1) == ctr)
			{
				if(totalAccountFreeSpacePercent < 100)
				{
					diffFromHundred = 100 - totalAccountFreeSpacePercent;
					perAccountFreeSpacePercent = perAccountFreeSpacePercent+diffFromHundred;
				}
				if(totalAccountFreeSpacePercent > 100)
				{
					diffFromHundred = totalAccountFreeSpacePercent - 100;
					perAccountFreeSpacePercent = perAccountFreeSpacePercent-diffFromHundred;
				}
			}
		}
		else/* Linked accounts less or equal to max file splits allowed? */
		{
			/* If it's the last iteration, total account percentage should be 100 by the time we reach here.
			If not 100 already, round-off accordingly with the perAccountFreeSpacePercent of the last iteration */
			if((totalLinkedAccounts-1) == ctr)
			{
				if(totalAccountFreeSpacePercent < 100)
				{
					diffFromHundred = 100 - totalAccountFreeSpacePercent;
					perAccountFreeSpacePercent = perAccountFreeSpacePercent+diffFromHundred;
				}
				if(totalAccountFreeSpacePercent > 100)
				{
					diffFromHundred = totalAccountFreeSpacePercent - 100;
					perAccountFreeSpacePercent = perAccountFreeSpacePercent-diffFromHundred;
				}
			}
		}
		perAccountFreeSpaceStat = perAccountFreeSpacePercent;
	}

	return perAccountFreeSpaceStat;
}

char *brewEngine_CalcBrewScore(char *linkedAccountsJSON)
{
	char brewScoreJSON[MAX_LEN*2] = {'\0'}, brewScoreJSONSingle[MAX_LEN] = {'\0'};
	char accountNameFmtIndex0[SHORT_LEN] = {'\0'}, accountNameFmtIndex1[SHORT_LEN] = {'\0'}, accountNameFmtIndex2[SHORT_LEN] = {'\0'};
	char *brewScore = MEM_MALLOC(MAX_LEN*2);
	char *accountNameFmt;

	double totalAccountFreeSpace = 0,  perAccountFreeSpace = 0;
	int perAccountFreeSpacePercent = 0, totalAccountFreeSpacePercent = 0, perAccountFreeSpacePercentPart1 = 0, perAccountFreeSpacePercentPart2 = 0, remAccountPercent = 0;
	int perAccountFreeSpacePercentIndex0 = 0, perAccountFreeSpacePercentIndex1 = 0, perAccountFreeSpacePercentIndex2 = 0, perAccountFreeSpacePercentLargest = 0;
	int index = 0, ctr=0;

	/* Get the number of accounts. This is the total number of all linked accounts */
	cJSON *cjson_AccountsLinked = cJSON_Parse(linkedAccountsJSON);
	cJSON *cjson_AccountsTotal = cJSON_GetObjectItem(cjson_AccountsLinked, ACCOUNTS);
	int totalLinkedAccounts = cJSON_GetArraySize(cjson_AccountsTotal);

	/* TODO: Also retrieve MFS information per account as part of the brewScore calculation process that follows below */

	/* Just 1 linked account, so split as 25:25:25:25 and store within the same account */
	if(totalLinkedAccounts == 1)
	{
		/* Get the name of the account with index=0 */
		accountNameFmt = brewEngine_GetPerAccountName(index, cjson_AccountsTotal);

		snprintf(brewScoreJSON, MAX_LEN*2, "{\"%s\": [{\"%s\": \"%s\",\"%s\": 100}]}", BREWSCORE, ACCOUNTNAME, accountNameFmt, ACCOUNTPERCENT);
		strncpy(brewScore, brewScoreJSON, MAX_LEN*2);
	}
	else if(totalLinkedAccounts == 2)
	{
		/* Iterate through the linked accounts JSON and calculate the total free account space available */
		for (index=0, ctr=0; index<totalLinkedAccounts; index++, ctr++)
		{
			perAccountFreeSpace = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, TOTAL_ACS_FS_NOTCALC, TOTAL_ACS_FS_PERCENT_NOTCALC);

			/* Keep adding all the per account free space to get the total free space */
			totalAccountFreeSpace += perAccountFreeSpace;
		}

		snprintf(brewScoreJSON, MAX_LEN*2, "{\"%s\": [", BREWSCORE);

		/* Iterate through the linked accounts JSON and calculate per account free space v/s total free space for weighted mean file splitting */
		for(index=0, ctr=0; index<totalLinkedAccounts; index++, ctr++)
		{
			totalAccountFreeSpacePercent = totalAccountFreeSpacePercent + perAccountFreeSpacePercent;
			perAccountFreeSpacePercent = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, totalAccountFreeSpace, totalAccountFreeSpacePercent);

			/* Get the name of the account in this iteration */
			accountNameFmt = brewEngine_GetPerAccountName(index, cjson_AccountsTotal);

			/* What we're essentialy doing here is that the above obtained perAccountFreeSpacePercent is equally divided again for storing within the same account */
			remAccountPercent = perAccountFreeSpacePercent%2;
			if (remAccountPercent == 0)
			{
				perAccountFreeSpacePercentPart1 = perAccountFreeSpacePercent/2;
				perAccountFreeSpacePercentPart2 = perAccountFreeSpacePercentPart1;
			}
			else
			{
				perAccountFreeSpacePercentPart1 = perAccountFreeSpacePercent/2;
				perAccountFreeSpacePercentPart2 = perAccountFreeSpacePercentPart1 + remAccountPercent;
			}
			/* It's because of the above logic of storing two equal splits within the same accounts, we need to make double entry in the JSON with the percent arrived above */
			snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}", ACCOUNTNAME, accountNameFmt, ACCOUNTPERCENT, perAccountFreeSpacePercentPart1, ACCOUNTNAME, accountNameFmt, ACCOUNTPERCENT, perAccountFreeSpacePercentPart2);
			strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);

			if(ctr == (totalLinkedAccounts-1))/* Complete JSON if it's the last */
				strcat(brewScoreJSON, "]}");
			else /* Continue with JSON construction by appending a "comma" at the end */
				strcat(brewScoreJSON, ",");
		}
		strncpy(brewScore, brewScoreJSON, MAX_LEN*2);
	}
	else if(totalLinkedAccounts == 3)
	{
		/* Iterate through the linked accounts JSON and calculate the total free account space available */
		for (index=0, ctr=0; index<totalLinkedAccounts; index++)
		{
			perAccountFreeSpace = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, TOTAL_ACS_FS_NOTCALC, TOTAL_ACS_FS_PERCENT_NOTCALC);

			/* Keep adding all the per account free space to get the total free space */
			totalAccountFreeSpace += perAccountFreeSpace;
		}

		snprintf(brewScoreJSON, MAX_LEN*2, "{\"%s\": [", BREWSCORE);

		/* Iterate through the linked accounts JSON and calculate per account free space v/s total free space for weighted mean file splitting */
		for(index=0, ctr=0; index<totalLinkedAccounts; index++)
		{
			totalAccountFreeSpacePercent = totalAccountFreeSpacePercent + perAccountFreeSpacePercent;
			perAccountFreeSpacePercent = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, totalAccountFreeSpace, totalAccountFreeSpacePercent);

			/* Depending on the iteration, store the per account free space percentage and account name */
			if(index == 0)
			{
				perAccountFreeSpacePercentIndex0 = perAccountFreeSpacePercent;
				snprintf(accountNameFmtIndex0, SHORT_LEN, "%s", brewEngine_GetPerAccountName(index, cjson_AccountsTotal));
			}
			else if(index == 1)
			{
				perAccountFreeSpacePercentIndex1 = perAccountFreeSpacePercent;
				snprintf(accountNameFmtIndex1, SHORT_LEN, "%s", brewEngine_GetPerAccountName(index, cjson_AccountsTotal));
			}
			else if(index == 2)
			{
				perAccountFreeSpacePercentIndex2 = perAccountFreeSpacePercent;
				snprintf(accountNameFmtIndex2, SHORT_LEN, "%s", brewEngine_GetPerAccountName(index, cjson_AccountsTotal));
			}

			if(ctr == (totalLinkedAccounts-1))/* Check if it's the last iteration */
			{
				/* Determine the largest free space percent of the 3 accounts. Set a flag as well if it's the largest */
				if((perAccountFreeSpacePercentIndex0 >= perAccountFreeSpacePercentIndex1) && (perAccountFreeSpacePercentIndex0 >= perAccountFreeSpacePercentIndex2))
				{
					perAccountFreeSpacePercentLargest = perAccountFreeSpacePercentIndex0;
					perAccountFreeSpacePercentIndex0 = FREE_SPACE_PERCENT_LARGEST;
				}
				else if((perAccountFreeSpacePercentIndex1 >= perAccountFreeSpacePercentIndex0) && (perAccountFreeSpacePercentIndex1 >= perAccountFreeSpacePercentIndex2))
				{
					perAccountFreeSpacePercentLargest = perAccountFreeSpacePercentIndex1;
					perAccountFreeSpacePercentIndex1 = FREE_SPACE_PERCENT_LARGEST;
				}
				else
				{
					perAccountFreeSpacePercentLargest = perAccountFreeSpacePercentIndex2;
					perAccountFreeSpacePercentIndex2 = FREE_SPACE_PERCENT_LARGEST;
				}

				/* Construct the first part of JSON with the non-largest account free space percentage info */
				if((perAccountFreeSpacePercentIndex0 != FREE_SPACE_PERCENT_LARGEST) && (perAccountFreeSpacePercentIndex1 != FREE_SPACE_PERCENT_LARGEST))
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}, ", ACCOUNTNAME, accountNameFmtIndex0, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex0, ACCOUNTNAME, accountNameFmtIndex1, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex1);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}
				else if((perAccountFreeSpacePercentIndex1 != FREE_SPACE_PERCENT_LARGEST) && (perAccountFreeSpacePercentIndex2 != FREE_SPACE_PERCENT_LARGEST))
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}, ", ACCOUNTNAME, accountNameFmtIndex1, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex1, ACCOUNTNAME, accountNameFmtIndex2, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex2);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}
				else if((perAccountFreeSpacePercentIndex0 != FREE_SPACE_PERCENT_LARGEST) && (perAccountFreeSpacePercentIndex2 != FREE_SPACE_PERCENT_LARGEST))
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}, ", ACCOUNTNAME, accountNameFmtIndex0, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex0, ACCOUNTNAME, accountNameFmtIndex2, ACCOUNTPERCENT, perAccountFreeSpacePercentIndex2);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}

				/* Split the percentage again for the largest account for equal distribution */
				remAccountPercent = perAccountFreeSpacePercentLargest%2;
				if (remAccountPercent == 0)
				{
					perAccountFreeSpacePercentPart1 = perAccountFreeSpacePercentLargest/2;
					perAccountFreeSpacePercentPart2 = perAccountFreeSpacePercentPart1;
				}
				else
				{
					perAccountFreeSpacePercentPart1 = perAccountFreeSpacePercentLargest/2;
					perAccountFreeSpacePercentPart2 = perAccountFreeSpacePercentPart1 + remAccountPercent;
				}

				/* Construct the second part of JSON with the largest account free space percentage info split up */
				if(perAccountFreeSpacePercentIndex0 == FREE_SPACE_PERCENT_LARGEST)
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}]}", ACCOUNTNAME, accountNameFmtIndex0, ACCOUNTPERCENT, perAccountFreeSpacePercentPart1, ACCOUNTNAME, accountNameFmtIndex0, ACCOUNTPERCENT, perAccountFreeSpacePercentPart2);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}
				else if(perAccountFreeSpacePercentIndex1 == FREE_SPACE_PERCENT_LARGEST)
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}]}", ACCOUNTNAME, accountNameFmtIndex1, ACCOUNTPERCENT, perAccountFreeSpacePercentPart1, ACCOUNTNAME, accountNameFmtIndex1, ACCOUNTPERCENT, perAccountFreeSpacePercentPart2);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}
				else if(perAccountFreeSpacePercentIndex2 == FREE_SPACE_PERCENT_LARGEST)
				{
					snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}, {\"%s\": \"%s\",\"%s\": %d}]}", ACCOUNTNAME, accountNameFmtIndex2, ACCOUNTPERCENT, perAccountFreeSpacePercentPart1, ACCOUNTNAME, accountNameFmtIndex2, ACCOUNTPERCENT, perAccountFreeSpacePercentPart2);
					strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);
				}
			}
		}
		strncpy(brewScore, brewScoreJSON, MAX_LEN*2);
	}
	else if(totalLinkedAccounts == 4)
	{
		/* Iterate through the linked accounts JSON and calculate the total free account space available */
		for (index=0, ctr=0; index<totalLinkedAccounts; index++, ctr++)
		{
			perAccountFreeSpace = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, TOTAL_ACS_FS_NOTCALC, TOTAL_ACS_FS_PERCENT_NOTCALC);

			/* Keep adding all the per account free space to get the total free space */
			totalAccountFreeSpace += perAccountFreeSpace;
		}

		snprintf(brewScoreJSON, MAX_LEN*2, "{\"%s\": [", BREWSCORE);

		/* Iterate through the linked accounts JSON and calculate per account free space v/s total free space for weighted mean file splitting */
		for(index=0, ctr=0; index<totalLinkedAccounts; index++,ctr++)
		{
			totalAccountFreeSpacePercent = totalAccountFreeSpacePercent + perAccountFreeSpacePercent;
			perAccountFreeSpacePercent = brewEngine_GetPerAccountFreeSpaceStats(ctr, index, cjson_AccountsTotal, totalAccountFreeSpace, totalAccountFreeSpacePercent);

			/* Get the name of the account in this iteration */
			accountNameFmt = brewEngine_GetPerAccountName(index, cjson_AccountsTotal);

			snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}", ACCOUNTNAME, accountNameFmt, ACCOUNTPERCENT, perAccountFreeSpacePercent);
			strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);

			if(ctr == (totalLinkedAccounts-1))/* Complete JSON if it's the last */
				strcat(brewScoreJSON, "]}");
			else /* Continue with JSON construction by appending a "comma" at the end */
				strcat(brewScoreJSON, ",");
		}
		strncpy(brewScore, brewScoreJSON, MAX_LEN*2);
	}
	else if(totalLinkedAccounts > 4)
	{
		int linkedAccountsList[totalLinkedAccounts], randomAccountsList[FILE_SPLIT_MAX];
		int random = 0, temp = 0;

		srand(time(NULL));

		/* Populate the linked accounts array in sequence from 0 to total linked accounts */
		for(index=0; index<totalLinkedAccounts; index++)
		{
			linkedAccountsList[index] = index;
		}

		/* Populate the random selected accounts array based on number of file splits.
		We assign -1 to array item of the linked accounts array to ensure uniqueness (for not being picked up again)  */
		for(index=0; index<FILE_SPLIT_MAX; index++)
		{
			random = rand() % totalLinkedAccounts;
			temp = linkedAccountsList[random];

			if (linkedAccountsList[random] != -1)
			{
				randomAccountsList[index] = temp;
				linkedAccountsList[random] = -1;
			}
			else /* Decrement the counter to repeat the loop again for that lost iteration */
				index--;
		}

		/* Iterate through the linked accounts JSON and calculate the total free account space available */
		for (index=0, ctr=0; index<FILE_SPLIT_MAX; index++, ctr++)
		{
			perAccountFreeSpace = brewEngine_GetPerAccountFreeSpaceStats(ctr, randomAccountsList[index], cjson_AccountsTotal, TOTAL_ACS_FS_NOTCALC, TOTAL_ACS_FS_PERCENT_NOTCALC);
			/* Keep adding all the per account free space to get the total free space */
			totalAccountFreeSpace += perAccountFreeSpace;
		}

		snprintf(brewScoreJSON, MAX_LEN*2, "{\"%s\": [", BREWSCORE);

		/* Iterate through the linked accounts JSON and calculate per account free space v/s total free space for weighted mean file splitting */
		for(index=0, ctr=0; index<FILE_SPLIT_MAX; index++, ctr++)
		{
			totalAccountFreeSpacePercent = totalAccountFreeSpacePercent + perAccountFreeSpacePercent;
			perAccountFreeSpacePercent = brewEngine_GetPerAccountFreeSpaceStats(ctr, randomAccountsList[index], cjson_AccountsTotal, totalAccountFreeSpace, totalAccountFreeSpacePercent);
			/* Get the name of the account in this iteration */
			accountNameFmt = brewEngine_GetPerAccountName(randomAccountsList[index], cjson_AccountsTotal);

			snprintf(brewScoreJSONSingle, MAX_LEN, "{\"%s\": \"%s\",\"%s\": %d}", ACCOUNTNAME, accountNameFmt, ACCOUNTPERCENT, perAccountFreeSpacePercent);
			strncat(brewScoreJSON, brewScoreJSONSingle, MAX_LEN*2);

			if(ctr == (FILE_SPLIT_MAX-1))/* Complete JSON if it's the last */
				strcat(brewScoreJSON, "]}");
			else /* Continue with JSON construction by appending a "comma" at the end */
				strcat(brewScoreJSON, ",");
		}
		strncpy(brewScore, brewScoreJSON, MAX_LEN*2);
	}

	free(cjson_AccountsTotal);
	cJSON_Delete(cjson_AccountsLinked);
	return brewScore;
}

