#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <string>

using namespace std;

class Files {
    string filename;
public:
    Files(string fname): filename(fname) {}
    int createDir(string userId);
};

int Files::createDir(string userId) {
    cout << "filename:" << filename << endl;
    return 0;
}

#endif /* FILE_HANDLING_H */
