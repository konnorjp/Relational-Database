#ifndef ColumnNamePair_h
#define ColumnNamePair_h

#include <iostream>

class ColNamePair {
public:
    ColNamePair(int col1, std::string name) {
        column1 = col1;
        this->name = name;
    };
    ~ColNamePair(){};
    
    int getColumn1() {
        return column1;
    }
    
    std::string getName() {
        return name;
    }
    
private:
    int column1;
    std::string name;
};

#endif /* ColumnNamePair_h */
