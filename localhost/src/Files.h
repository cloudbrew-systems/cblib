// The new version (src/cpp/fileHandling.h --> localhost/src/Files.h)
#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/stat.h>

#include "CBDefines.h"

class Files: public CBDefines {
public:
    Files(std::string _filename): filename(_filename) {}
    int createdir(std::string);
    unsigned long long int sizeinbytes(std::string);
    std::string shredsuffix(int);
    std::string getsha256hash(std::string);
    int deleteshreds(std::string, std::string);
    std::string encryptshreds(std::string, std::string, std::string, std::string, int);
private:
    std::string filename;
protected:
    const std::string FILES_TEMPDIR = "/tmp/upload";
    const std::string FILES_TEMPSHREDLIST = FILES_TEMPDIR + "/shredlist";
    const std::string FILES_TEMPSHREDCOUNT = FILES_TEMPDIR + "/shredcount";
    const std::string FILES_TEMPENCRYPTEDLIST = FILES_TEMPDIR + "/encryptedlist";
    const std::string FILES_TEMPENCRYPTEDCOUNT = FILES_TEMPDIR + "/encryptedcount";
    const std::string FILES_TEMPJOINLIST = FILES_TEMPDIR + "/joinlist";
    const std::string FILES_TEMPJOINCOUNT = FILES_TEMPDIR + "/joincount";
    // #define TEMP_ENCRYPTED_FILENAMEHASH TEMP_DIR"/encryptedFileNameHash"
    // #define TEMP_ENCRYPTED_COUNT TEMP_DIR"/encryptedCount"
};

#endif /* FILES_H */
