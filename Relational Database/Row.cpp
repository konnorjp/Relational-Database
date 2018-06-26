#include "Row.h"

bool Row::operator < (const Row& rhs) const {
    if (getSize() == 0 || rhs.getSize() == 0) return false;
    if (getSize() != rhs.getSize()) return false;
    for (unsigned long i = 0; i < getSize(); i++) {
        if (values[i] != rhs.values[i]) return (values[i] < rhs.values[i]);
    }
    return false;
}

bool Row::operator == (const Row& rhs) const {
    if (getSize() != rhs.getSize()) return false;
    return (rhs.values == values);
}

void Row::addValue(std::string value) {
    values.push_back(value);
}

void Row::removeAllColumnsBut(std::set<int> columnsToKeep) {
    std::vector<std::string> newValues;
    std::set<int>::iterator iter;
    for(iter = columnsToKeep.begin(); iter != columnsToKeep.end(); iter++) {
        newValues.push_back(values[*iter]);
    }
    values = newValues;
}

Row* Row::rearrangeRow(std::vector<int> orderMap) const {
    Row* rearrangedRow = new Row();
    for(unsigned long i = 0; i < orderMap.size(); i++) {
        rearrangedRow->addValue(values[orderMap[i]]);
    }
    return rearrangedRow;
}

void Row::print() const {
    for(unsigned long i = 0; i < values.size(); i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;
}

std::string Row::toString() const {
    std::stringstream ss;
    for(unsigned long i = 0; i < values.size(); i++) {
        ss << values[i];
    }
    ss << std::endl;
    return ss.str();
}

bool Row::matches(Row* row, std::vector<ColColPair> columnsToMerge) const {
    for(unsigned int i = 0; i < columnsToMerge.size(); i++) {
        if(values[columnsToMerge[i].getColumn1()] != row->values[columnsToMerge[i].getColumn2()]) {
            return false;
        }
    }
    return true;
}

Row* Row::mergeWith(Row* row, std::vector<ColColPair> columnsToMerge) const {
    std::vector<std::string> newValues = values;
    for(unsigned long i = 0; i < row->values.size(); i++) {
        bool merge = false;
        for(unsigned long j = 0; j < columnsToMerge.size(); j++) {
            if(i == columnsToMerge[j].getColumn2()) merge = true;
        }
        if(!merge) newValues.push_back(row->values[i]);
    }
    Row* newRow = new Row(newValues);
    return newRow;
}


