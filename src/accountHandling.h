
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ACCOUNT_HANDLING_H
#define ACCOUNT_HANDLING_H

#define UID "UID"

#define HUNDRED_PARTS 100
#define SINGLE_LINKED_ACCOUNT 1

#define ACCOUNTNAME "AN"
#define ACCOUNTPERCENT "AP"
#define ACCOUNTS "ACS"

#define ACCOUNT_GOOGLEDRIVE "GoogleDrive"
#define ACCOUNT_ONEDRIVE "OneDrive"
#define ACCOUNT_BOX "Box"
#define ACCOUNT_DROPBOX "Dropbox"

char *accountHandling_GetPercentFromBrewScore(char *brewScore, int index);
char* accountHandling_GetNameFromBrewScore(char *brewScore, int index);

char* accountHandling_GetNameFromLinkedAccounts(char *linkedAccountsJSON, int index);
double accountHandling_GetTotalSpaceFromLinkedAccounts(char *linkedAccountsJSON, int index);
double accountHandling_GetUsedSpaceFromLinkedAccounts(char *linkedAccountsJSON, int index);
double accountHandling_GetMaxFileSizeFromLinkedAccounts(char *linkedAccountsJSON, int index);

#endif /* ACCOUNT_HANDLING_H */

#ifdef __cplusplus
}
#endif

