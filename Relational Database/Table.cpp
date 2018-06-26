#include "Table.h"
#include "ColColPair.h"

void Table::addRow(Row* row) {
    rows.insert(*row);
}

Table* Table::select(std::vector<SelectionKey*> selectionKeys) {
    // The column/value needs to make sure that column is a viable column
    // Both columns need to be in the table, check
    Table* result = new Table(name, Header(header));
    std::set<Row>::iterator iter;
    for (iter = rows.begin(); iter != rows.end(); iter++) {
        bool satisfied = true;
        for(unsigned long j = 0; j < selectionKeys.size(); j++) {
            satisfied = selectionKeys[j]->satisfies(*iter);
            if(!satisfied) break;
        }
        if(satisfied) result->addRow(new Row(*iter));
    }
    return result;
}

Table* Table::project(std::set<int> columnsToKeep) {
    // It might try to access a field that doesn't exist
    Table* result = new Table(name, new Header(header));
    result->header.removeAllColumnsBut(columnsToKeep);
    std::set<Row>::iterator iter;
    for (iter = rows.begin(); iter != rows.end(); iter++) {
        Row* newRow = new Row(*iter);
        newRow->removeAllColumnsBut(columnsToKeep);
        result->addRow(newRow);
    }
    return result;
}

Table* Table::rename(std::vector<ColNamePair> newNames) {
    // The columns need to exist!!!!
    Table* result = new Table(name, Header(header));
    for (unsigned long i = 0; i < newNames.size(); i++) {
        result->header.rename(newNames[i].getColumn1(), newNames[i].getName());
    }
    std::set<Row>::iterator iter;
    for (iter = rows.begin(); iter != rows.end(); iter++) {
        Row* newRow = new Row(*iter);
        result->addRow(newRow);
    }
    return result;
}
Table* Table::rename(std::string name, std::vector<ColNamePair> newNames) {
    Table* result = rename(newNames);
    result->name = name;
    return result;
}

void Table::print() const {
    std::cout << name << std::endl;
    header.print();
    std::set<Row>::iterator iter;
    for (iter = rows.begin(); iter != rows.end(); iter++) {
        iter->print();
    }
}

std::string Table::toString() const {
    std::stringstream ss;
    ss << name << std::endl << header.toString();
    std::set<Row>::iterator iter;
    for (iter = rows.begin(); iter != rows.end(); iter++) {
        ss << iter->toString();
    }
    return ss.str();
}

std::string Table::answerQuery() const {
    std::stringstream ss;
    std::set<Row>::iterator iter;
    for(iter = rows.begin(); iter != rows.end(); iter++) {
        unsigned long numCol = header.columnNames.size();
        if (numCol > 0) {
            ss << std::endl << "  ";
            for(unsigned long i = 0; i < numCol; i++) {
                ss << header.columnNames[i] << "=" << iter->values[i];
                if (i < numCol - 1) {
                    ss << ", ";
                }
            }
        }
    }
    return ss.str();
}

void Table::unite(Table* table) {
    std::vector<int> newOrderInMap = header.createOrderMap(table->header);
    if (newOrderInMap.size() != header.columnNames.size()) return;
    std::set<Row>::iterator iter;
    for(iter = table->rows.begin(); iter != table->rows.end(); iter++) {
        Row* rearrangedRow = iter->rearrangeRow(newOrderInMap);
        addRow(rearrangedRow);
    }
}

Table* Table::naturalJoin(Table* table) {
    std::vector<ColColPair> columnsToMerge = header.getColumnsToMerge(table->header);
    //if(columnsToMerge.size() < 1) return new Table(*this);
    Header resultHeader = header.mergeWith(table->header, columnsToMerge);
    Table* result = new Table(name, resultHeader); //Giving it the same name as the first table
    std::set<Row>::iterator iter;
    std::set<Row>::iterator it;
    for(it = rows.begin(); it != rows.end(); it++) {
        for(iter = table->rows.begin(); iter != table->rows.end(); iter++) {
            Row matchingRow = *iter;
            if(it->matches(&matchingRow, columnsToMerge)) {
                //Row mergeRow = *iter;
                result->addRow(it->mergeWith(&matchingRow, columnsToMerge));
            }
        }
    }
    
    return result;
}



