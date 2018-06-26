#ifndef ColValueKey_h
#define ColValueKey_h

#include <iostream>
#include "SelectionKey.h"

class ColValueKey : public SelectionKey {
public:
    ColValueKey(int col1, std::string value) {
        column = col1;
        this->value = value;
    };
    ~ColValueKey(){};
    
    int getColumn() {
        return column;
    }
    
    std::string getValue() {
        return value;
    }
    
    bool satisfies(Row row) {
        return (row.values[column] == value);
    }
private:
    
    int column;
    std::string value;
};
#endif /* ColValueKey_h */
