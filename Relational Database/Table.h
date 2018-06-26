#ifndef Table_h
#define Table_h

#include <iostream>
#include <set>
#include "Header.h"
#include "Row.h"
#include "SelectionKey.h"
#include "ColumnNamePair.h"
#include <sstream>

class Table {
public:
    Table(const Table& table) : header(table.header) {
        name = table.name;
        rows = table.rows;
    }
    Table(const std::string& name, const Header& header) : header(header) {
        this->name = name;
    }
    Table(const Header& header) : header(header) {}
    ~Table(){};
    
    
    void addRow(Row* row);
    Table* select(std::vector<SelectionKey*> selectionKeys);
    Table* project(std::set<int> columnsToKeep);
    Table* rename(std::vector<ColNamePair> newNames);
    Table* rename(std::string name, std::vector<ColNamePair> newNames);
    void unite(Table* table);
    Table* naturalJoin(Table* table);
    
    void print() const;
    std::string toString() const;
    unsigned long getRowSize() const { return rows.size(); };
    std::string answerQuery() const;
    Header* getHeader() {
        return &header;
    }
    std::string getName() {
        return name;
    }
    
private:
    std::string name;
    Header header;
    std::set<Row> rows;
};

#endif /* Table_h */
