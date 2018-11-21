// The new version (src/cpp/cbDefines.h --> localhost/src/CBDefines.h)
#ifndef CB_DEFINES_H
#define CB_DEFINES_H

#include <iostream>
#include <string>

class CBDefines {
protected:
    // TODO: Revisit all of them at later stage and delete if unused
    const std::string CB_QUIETLY = "> /dev/null 2>&1";
    const std::string CB_DEFAULT_CIPHER = "AES256";
    const std::string STR_SUCCESS = "SUCCESS";
    const std::string STR_FAIL = "FAIL";
    const std::string STR_ERROR = "ERROR";
    const std::string STR_RESULT = "RESULT";
    const std::string TYPE = "TYPE";
    const std::string STR_PSV = "PSV";
    const std::string STR_S3 = "S3";
    const std::string ENCRYPTED = "ENC";
    const std::string SPLIT = "SPLT";
    const int CB_SUCCESS = 0;
    const int CB_FAIL = 1;
    const int CB_ERROR = 2;
    const int MAX_CMD_LEN = 256;
    const int MAX_LEN = 128;
    const int SHORT_LEN = 64;
    const int BYTE_LEN = 8;
    const int NIBBLE_LEN = 4;
};

#endif /* CB_DEFINES_H */
