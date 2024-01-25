//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_WRITEBYTESTOFILE_H
#define PHP_COMPILER_WRITEBYTESTOFILE_H

#include <string>
#include <fstream>
#include <vector>
#include "code_generation/bytes/ValueAndBytes.h"

using namespace std;

class WriteBytesToFile {
private:
    ofstream *out;
public:
    explicit WriteBytesToFile(const char* filePath) {
        out = new ofstream(filePath, ios::binary | ios::out);
    }

    void write(ValueAndBytes value) {
        out->write(value.getValue(), value.getBytes());
    }

    void write(vector<ValueAndBytes *> &values) {
        for (auto value : values) {
            out->write(value->getValue(), value->getBytes());
        }
    }

    void close() {
        out->close();
    }
};

#endif //PHP_COMPILER_WRITEBYTESTOFILE_H
