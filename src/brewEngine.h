
#ifdef __cplusplus
extern "C" {
#endif

#ifndef BREW_ENGINE_H
#define BREW_ENGINE_H

#include "cJSON.h"

#define BREWSCORE "BS"
#define TOTALSPACE "TS"
#define USEDSPACE "US"
#define MAXFILESIZE "MFS"

#define TOTAL_ACS_FS_NOTCALC -1
#define TOTAL_ACS_FS_PERCENT_NOTCALC -1
#define FREE_SPACE_PERCENT_LARGEST 999

char *brewEngine_CalcBrewScore(char *linkedAccountsJSON);
char* brewEngine_CleanupQuotes(char *accountName);
char* brewEngine_CleanupID(char *accountName);
char* brewEngine_CleanupHash(char *accountName);
char *brewEngine_GetPerAccountName(int index, cJSON *cjson_AccountsTotal);
double brewEngine_GetPerAccountFreeSpaceStats(int ctr, int index, cJSON *cjson_AccountsTotal, double totalAccountFreeSpace, int totalAccountPercent);

#endif /* BREW_ENGINE_H */

#ifdef __cplusplus
}
#endif

