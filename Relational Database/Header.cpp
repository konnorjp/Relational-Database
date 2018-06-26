#include "Header.h"

bool Header::operator == (const Header& rhs) const {
    //if (getSize() != rhs.getSize()) return false;
    return (rhs.columnNames == columnNames);
}

void Header::rename(int column, std::string newName) {
    //if (column > columnNames.size() - 1 || column < 0) return;
    columnNames[column] = newName;
}

void Header::removeAllColumnsBut(std::set<int> columnsToKeep) {
    std::vector<std::string> newColumnNames;
    std::set<int>::iterator iter;
    for(iter = columnsToKeep.begin(); iter != columnsToKeep.end(); iter++) {
        newColumnNames.push_back(columnNames[*iter]);
    }
    columnNames = newColumnNames;
}

void Header::print() const {
    for(unsigned long i = 0; i < columnNames.size(); i++) {
        std::cout << columnNames[i] << " ";
    }
    std::cout << std::endl;
}

std::string Header::toString() const {
    std::stringstream ss;
    for(unsigned long i = 0; i < columnNames.size(); i++) {
        ss << columnNames[i];
    }
    ss << std::endl;
    return ss.str();
}

std::vector<int> Header::createOrderMap(const Header& header) const{
    std::vector<int> orderMap;
    for(unsigned long i = 0; i < columnNames.size(); i++) {
        for(unsigned long j = 0; j < header.columnNames.size(); j++) {
            if (columnNames[i] == header.columnNames[j]) {
                orderMap.push_back(int(j));
            }
        }
    }
    return orderMap;
}

std::vector<ColColPair> Header::getColumnsToMerge(const Header& header) const {
    std::vector<ColColPair> columnsToMerge; //Column1 is in first header and Column2 in second
    for(unsigned long i = 0; i < header.columnNames.size(); i++) {
        for(unsigned long j = 0; j < columnNames.size(); j++) {
            if(header.columnNames[i] == columnNames[j]) {
                columnsToMerge.push_back(ColColPair(int(j),int(i)));
            }
        }
    }
    return columnsToMerge;
}

Header Header::mergeWith(const Header& header, const std::vector<ColColPair> columnsToMerge) const {
    std::vector<std::string> newColumnNames;
    newColumnNames = columnNames;
    for(unsigned long i = 0; i < header.columnNames.size(); i++) {
        bool merge = false;
        for(unsigned long j = 0; j < columnsToMerge.size(); j++) {
            if(i == columnsToMerge[j].getColumn2()) merge = true;
        }
        if(!merge) newColumnNames.push_back(header.columnNames[i]);
    }
    Header newHeader = Header(newColumnNames);
    return newHeader;
}

