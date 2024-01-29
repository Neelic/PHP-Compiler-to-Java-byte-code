//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_VALUEANDBYTES_H
#define PHP_COMPILER_VALUEANDBYTES_H

#include <algorithm>
#include <string>
#include <stdexcept>
#include "iostream"

using namespace std;

class ValueAndBytes {
private:
    enum TypeValueByte {
        none = 0,
        intVal = 1,
        floatVal = 2,
        charVal = 3,
    };

    TypeValueByte type = none;
    int valueInt = -1;
    float valueFloat = -1;
    string valueChar;
    int bytes;
    bool isNeedReverseBytes = false;

public:
    void reverseBytes() const {
        char *start;
        if (type == intVal) start = (char *) &valueInt;
        else if (type == floatVal) start = (char *) &valueFloat;
        else if (type == charVal || type == none) return;

        char *iStart = start, *iEnd = iStart + bytes;
        reverse(iStart, iEnd);
    }

    ValueAndBytes(const int &value, int bytes, bool isReverseBytes = true) {
        this->isNeedReverseBytes = isReverseBytes;
        this->valueInt = value;
        this->bytes = bytes;
        this->type = intVal;
    }

    ValueAndBytes(const float &value, int bytes, bool isReverseBytes = true) {
        this->isNeedReverseBytes = isReverseBytes;
        this->valueFloat = value;
        this->bytes = bytes;
        this->type = floatVal;
    }

    explicit ValueAndBytes(const string &value) {
        this->valueChar = value;
        this->bytes = (int) value.length();
        this->type = charVal;
    }

    int getBytes() const {
        return bytes;
    }

    const char *getValue() const {
        if (type == intVal) {
            return (const char *) &valueInt;
        } else if (type == floatVal) {
            return (const char *) &valueFloat;
        } else if (type == charVal)
            return valueChar.c_str();

        throw runtime_error("Failed to get null value");
    }

    bool isNeedReverse() const {
        return isNeedReverseBytes;
    }

    bool operator==(ValueAndBytes &other) {
        return type == other.type && valueInt == other.valueInt && valueFloat == other.valueFloat &&
               valueChar == other.valueChar;
    }
};


#endif //PHP_COMPILER_VALUEANDBYTES_H
