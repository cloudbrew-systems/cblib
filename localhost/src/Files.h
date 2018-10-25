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
private:
    std::string filename;
protected:
    const std::string FILES_TEMPDIR = "/tmp/upload";
};

#endif /* FILES_H */
