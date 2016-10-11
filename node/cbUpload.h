//#include <stdio.h>
//#include <stdlib.h>

//#include "accountHandling.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CB_UPLOAD_NODE_H
#define CB_UPLOAD_NODE_H

//#ifndef NULL
//#define NULL 0
//#endif

//struct accounts {
	//const char *accountName;
	//unsigned long long int totalSpace;
	//unsigned long long int usedSpace;
	//unsigned long long int maxFilesize;
//};

//typedef struct uploadInfo {
	//int uid;
	//const char *filename;
	//struct accounts myAccounts[MAX_LINKED_ACCOUNTS];
//}uploadInfo;

//typedef struct rain_result {
	//float median;
	//float mean;
	//float standard_deviation;
	//int n;
//}rain_result;

//int cb_upload(char *fileAbsLoc, char *fileName, char*userId, char *linkedAccountsJSON);
char *cb_upload(char *uploadInfo);

#endif /* CB_UPLOAD_NODE_H */

#ifdef __cplusplus
}
#endif

