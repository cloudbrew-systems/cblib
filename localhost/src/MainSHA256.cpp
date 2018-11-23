#include <iostream>
#include <string>
#include "SHA256.h"

int main(int argc, char** argv) {
    SHA256 sha;
    std::string strval = sha.sha256strval(std::string{argv[1]});
    std::string filepath = sha.sha256filepath(std::string{argv[1]});

    std::cout << "SHA256 hash of string " << argv[1] << " is " << strval << std::endl;
    std::cout << "SHA256 hash of file " << argv[1] << " is " << filepath << std::endl;

     return 0;
}
