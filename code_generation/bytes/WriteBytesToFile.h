//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_WRITEBYTESTOFILE_H
#define PHP_COMPILER_WRITEBYTESTOFILE_H

#include <string>
#include <fstream>
#include "code_generation/bytes/ValueAndBytes.h"

using namespace std;

class WriteBytesToFile {
private:
    ofstream *out;
public:
    WriteBytesToFile(string &filePath) {
        out = new ofstream(filePath, ios::binary | ios::out);
    }

    void write(ValueAndBytes value) {
        out->write(value.getValue(), value.getBytes());
    }

    void close() {
        out->close();
    }
};

#endif //PHP_COMPILER_WRITEBYTESTOFILE_H
