// The new version (src/cpp/FileHandling.h --> localhost/src/Files.h)
#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <memory>
#include <sys/stat.h>

#include "cbDefines.h"

class Files {
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
    const std::string FILES_TEMPSHREDLIST = FILES_TEMPDIR + "/shredFilesList";
    // #define TEMP_SHRED_COUNT_FILE TEMP_DIR"/shredCount"
    // #define TEMP_ENCRYPT_COUNT_FILE TEMP_DIR"/encryptCount"
    // #define TEMP_ENCRYPTED_FILESLIST TEMP_DIR"/encryptFilesList"
    // #define TEMP_JOIN_FILELIST TEMP_DIR"/joinFileList"
    // #define TEMP_JOIN_COUNT TEMP_DIR"/joinCount"
    // #define TEMP_ENCRYPTED_FILENAMEHASH TEMP_DIR"/encryptedFileNameHash"
    // #define TEMP_ENCRYPTED_COUNT TEMP_DIR"/encryptedCount"
};

#endif /* FILES_H */
