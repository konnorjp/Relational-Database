#ifndef ColColKey_h
#define ColColKey_h

#include <iostream>
#include "SelectionKey.h"

class ColColKey : public SelectionKey {
public:
    ColColKey(int col1, int col2) {
        column1 = col1;
        column2 = col2;
    };
    ~ColColKey(){};
    
    int getColumn1() const {
        return column1;
    }
    
    int getColumn2() const {
        return column2;
    }
    
    bool satisfies(Row row) {
        return (row.values[column1] == row.values[column2]);
    }
    
private:
    int column1;
    int column2;
};

#endif /* ColColKey_h */
