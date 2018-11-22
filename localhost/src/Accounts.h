// The new version (localhost/ref/accountHandling.h --> localhost/src/Accounts.h)
#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/stat.h>

#include "CBDefines.h"
#include "BrewEngine.h"

class Accounts: public CBDefines {
public:
    // See if the below 2 functions can be moved to BrewEngine class?
    std::string getpercentfrombrewscore(std::string brewScore, int index);
    std::string getnamefrombrewscore(std::string brewScore, int index);

    std::string getnamefromlinkedaccounts(std::string linkedAccountsJSON, int index);
    double gettotalspacefromlinkedaccounts(std::string linkedAccountsJSON, int index);
    double getusedspacefromlinkedaccounts(std::string linkedAccountsJSON, int index);
    double getmaxfilesizefromlinkedaccounts(std::string linkedAccountsJSON, int index);
// protected:
private:
    const std::string ACCOUNTS_UID = "UID";
    const int ACCOUNTS_HUNDREDPARTS = 100;
    const int ACCOUNTS_SINGLELINKEDACCOUNT = 1;
    const std::string ACCOUNTS_NAME = "AN";
    const std::string ACCOUNTS_PERCENT = "AP";
    const std::string ACCOUNTS = "ACS";
    const std::string ACCOUNTS_GOOGLEDRIVE = "GoogleDrive";
    const std::string ACCOUNTS_ONEDRIVE = "OneDrive";
    const std::string ACCOUNTS_BOX = "Box";
    const std::string ACCOUNTS_DROPBOX = "Dropbox";
};

#endif /* ACCOUNTS_H */
