#ifndef Row_h
#define Row_h

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include "ColColPair.h"

class Row {
public:
    Row(){}
    Row(std::vector<std::string> values) {
        this->values = values;
    }
    Row(Row* row) {
        values = row->values;
    }
    ~Row(){};
    
    bool operator < (const Row& rhs) const;
    bool operator == (const Row& rhs) const;
    
    void addValue(std::string value);
    void removeAllColumnsBut(std::set<int> columnsToKeep);
    Row* rearrangeRow(std::vector<int> orderMap) const;
    bool matches(Row* row, std::vector<ColColPair> columnsToMerge) const;
    Row* mergeWith(Row* row, std::vector<ColColPair> columnsToMerge) const;
    
    unsigned long getSize() const { return values.size(); }
    
    void print() const;
    std::string toString() const;
    std::vector<std::string> values;
};

#endif /* Row_h */
