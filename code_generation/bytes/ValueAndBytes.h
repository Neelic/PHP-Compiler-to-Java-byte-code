//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_VALUEANDBYTES_H
#define PHP_COMPILER_VALUEANDBYTES_H

#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

class ValueAndBytes {
private:
    void *value = nullptr;
    int bytes;

    static void reverseBytes(void *start, int size) {
        char *iStart = static_cast<char *>(start), *iEnd = iStart + size;
        reverse(iStart, iEnd);
    }

public:
    ValueAndBytes(unsigned int value, int bytes, bool isReverseBytes = true) {
        if (isReverseBytes) reverseBytes(&value, bytes);
        this->value = &value;
        this->bytes = bytes;
    }

    ValueAndBytes(const char *value, int bytes) {
        this->value = (void *) value;
        this->bytes = bytes;
    }

    int getBytes() const {
        return bytes;
    }

    char *getValue() {
        if (value != nullptr) return (char *) value;
        throw runtime_error("Failed to get null value");
    }
};


#endif //PHP_COMPILER_VALUEANDBYTES_H
