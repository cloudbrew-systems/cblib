// The new version (localhost/ref/brewEngine.h --> localhost/src/BrewEngine.h)
#ifndef BREWENGINE_H
#define BREWENGINE_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/stat.h>

#include "Files.h"
#include "Accounts.h"

class BrewEngine: public Files, public Accounts {
public:
    std::string calcbrewscore(std::string linkedaccountsjson);
    std::string cleanupquotes(std::string accountname);
    std::string cleanupid(std::string accountname);
    std::string cleanuphash(std::string accountname);
    std::string getperaccountname(int index, cJSON *accountstotal);
    double getperaccountfreespacestats(int ctr, int index, cJSON *accountstotal, double totalaccountfreespace, int totalaccountpercent);
// protected:
private:
    const std::string BE_BREWSCORE = "BS";
    const std::string BE_TOTALSPACE = "TS";
    const std::string BE_USEDSPACE = "US";
    const std::string BE_MAXFILESIZE = "MFS";
    const short BE_TOTALFREESPACENOTCALC = -1;
    const short BE_TOTALFREEPERCENTNOTCALC = -1;
    const short BE_FREESPACEPERCENTLARGEST = 999
};

#endif /* BREWENGINE_H */
