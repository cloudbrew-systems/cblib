// The new version (src/cpp/FileHandling.h --> localhost/src/Files.h)
#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>

class Files {
public:
    Files(std::string _filename): filename(_filename) {}
    int createDir(std::string userId);
private:
    std::string filename;
};

#endif /* FILES_H */
