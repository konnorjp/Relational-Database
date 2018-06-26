#ifndef ColColPair_h
#define ColColPair_h

#include <iostream>

class ColColPair {
public:
    ColColPair(int col1, int col2) {
        column1 = col1;
        column2 = col2;
    };
    ~ColColPair(){};
    
    int getColumn1() const {
        return column1;
    }
    
    int getColumn2() const {
        return column2;
    }
    
private:
    int column1;
    int column2;
};

#endif /* ColColPair_h */
