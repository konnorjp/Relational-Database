#ifndef Header_h
#define Header_h

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include "ColColPair.h"

class Header {
public:
    Header(std::vector<std::string> columnNames) {
        this->columnNames = columnNames;
        //check for duplicate columns by putting all columnNames in set and then comparing the size of columnNames and set. Nevermind its an assumption we can have
    }
    Header(Header* header) {
        columnNames = header->columnNames;
    }
    ~Header(){};
    
    bool operator == (const Header& rhs) const;
    
    void rename(int column, std::string newName);
    void removeAllColumnsBut(std::set<int> columnsToKeep);
    std::vector<int> createOrderMap(const Header& header) const;
    std::vector<ColColPair> getColumnsToMerge(const Header& header) const;
    Header mergeWith(const Header& header, const std::vector<ColColPair> columnsToMerge) const;
    
    void print() const;
    std::string toString() const;
    std::vector<std::string> columnNames;
};

#endif /* Header_h */
