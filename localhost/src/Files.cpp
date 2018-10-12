#include <iostream>
#include <string>
#include "Files.h"

// using namespace std;

int main(int argc, char **argv) {
    Files f("sample_file.jpg");
    f.createDir("120");

    return 0;
}
