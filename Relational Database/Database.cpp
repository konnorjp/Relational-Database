#include "Database.h"
#include "ColValueKey.h"
#include "ColColKey.h"
#include "ColumnNamePair.h"
#include <algorithm>

Database::Database(char* filename) {
    timesProcessRules = 0;
    datalog = new Datalog(filename);
    // Create all tables from Schemes
    std::vector<Scheme*> schemes = datalog->getSchemes()->getSchemes();
    for (unsigned long i = 0; i < schemes.size(); i++) {
        std::vector<std::string> columnNames;
        std::vector<Id*> columnIds = schemes[i]->getColumnNames();
        for( unsigned long j = 0; j < columnIds.size(); j++) {
            columnNames.push_back(columnIds[j]->toString());
        }
        Header* header = new Header(columnNames);
        std::string tableName = schemes[i]->getSchemeId()->toString();
        Table* table = new Table(tableName, header);
        tables.insert(std::pair<std::string, Table*>(tableName, table));
    }
    
    // Fill in all table rows from Facts
    std::vector<Fact*> facts = datalog->getFacts()->getFacts();
    for(unsigned long i = 0; i < facts.size(); i++) {
        std::vector<std::string> values;
        std::vector<StringClass*> valueStrings = facts[i]->getStrings();
        for(unsigned long j = 0; j < valueStrings.size(); j++) {
            values.push_back(valueStrings[j]->toString());
        }
        Row* row = new Row(values);
        std::string tableName = facts[i]->getFactId()->toString();
        (tables.find(tableName)->second)->addRow(row);
    }
}

void Database::processRules() {
    std::vector<Rule*> rules = datalog->getRules()->getRules();
    for(unsigned long i = 0; i < rules.size(); i++) {
        processRule(rules[i]);
    }
    timesProcessRules++;
    while(!nothingChanged) {
        nothingChanged = true;
        for(unsigned long i = 0; i < rules.size(); i++) {
            processRule(rules[i]);
        }
        timesProcessRules++;
    }
}

void Database::processOptimizedRules() {
    std::vector<std::vector<int>> SCC = datalog->getSCC();
    std::map<int, Rule*> ruleMapping = datalog->getRuleMapping();
    std::map<int,std::set<int>> graph = datalog->getGraph();
    std::cout << "Rule Evaluation\n";
    for(unsigned long m = 0; m < SCC.size(); m++) {
        std::sort(SCC[m].begin(), SCC[m].end());
        int timesProcessedSCC = 0;
        for(unsigned long i = 0; i < SCC[m].size(); i++) {
            Rule* rule = ruleMapping[SCC[m][i]];
            processRule(rule);
        }
        timesProcessedSCC++;
        
        //Determine if it has 1 rule and a self-loop
        bool trivial = false;
        if(SCC[m].size() == 1) {
            trivial = true;
            std::set<int>::iterator iter;
            for(iter = graph[SCC[m][0]].begin(); iter != graph[SCC[m][0]].end(); iter++) {
                if(*iter == SCC[m][0]) {
                    trivial = false;
                }
            }
        }
        
        while(!nothingChanged && !trivial) {
            nothingChanged = true;
            for(unsigned long i = 0; i < SCC[m].size(); i++) {
                Rule* rule = ruleMapping[SCC[m][i]];
                processRule(rule);
            }
            timesProcessedSCC++;
        }
        std::cout << timesProcessedSCC << " passes: ";
        for(unsigned long i = 0; i < SCC[m].size(); i++) {
            std::cout << "R" << SCC[m][i];
            if(i < SCC[m].size() - 1) std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Database::processRule(Rule* rule) {
    Table* table = getTable(rule->getHeadPredicate()->getHeadId()->toString());
    std::vector<std::string> tableColumnNames = table->getHeader()->columnNames;
    std::vector<Predicate*> predicates = rule->getPredicates();
    Table* result = processPredicate(predicates[0]);
    for(unsigned long i = 1; i < predicates.size(); i++) {
        Table* result2 = result->naturalJoin(processPredicate(predicates[i]));
        delete result;
        result = result2;
    }
    
    std::vector<SelectionKey*> selectionKeys;
    std::set<int> columnsToKeep;
    std::map<std::string, int> alreadySeenIds;
    std::vector<ColNamePair> colNamePairs;
    std::vector<Id*> ids = rule->getHeadPredicate()->getIds();
    
    std::vector<std::string> tableColNames = table->getHeader()->columnNames;
    std::vector<std::string> resultColNames = result->getHeader()->columnNames;
    for(unsigned long i = 0; i < tableColNames.size(); i++) {
        for(unsigned long j = 0; j < resultColNames.size(); j++) {
            if(ids[i]->toString() == resultColNames[j]) {
                columnsToKeep.insert(int(j));
            }
        }
    }
    
    Table* presult = result->project(columnsToKeep);
    resultColNames = presult->getHeader()->columnNames;
    for(unsigned long i = 0; i < tableColNames.size(); i++) {
        for(unsigned long j = 0; j < resultColNames.size(); j++) {
            if(ids[i]->toString() == resultColNames[j]) {
                colNamePairs.push_back(ColNamePair(int(j), tableColNames[int(i)]));
            }
        }
    }
    Table* rresult = presult->rename(table->getName(), colNamePairs);
    unsigned long numberTableRows = table->getRowSize();
    table->unite(rresult);
    unsigned long numberTableRowsAfterUnion = table->getRowSize();
    if(numberTableRows != numberTableRowsAfterUnion) nothingChanged = false;
    delete result;
    delete presult;
    delete rresult;
}

Table* Database::processPredicate(Predicate* predicate) {
    std::string tableName = predicate->getPredicateId()->toString();
    std::vector<Parameter*> parameters = predicate->getParameters();
    std::vector<SelectionKey*> selectionKeys;
    std::set<int> columnsToKeep;
    std::map<std::string, int> alreadySeenIds;
    std::vector<ColNamePair> colNamePairs;
    
    // Determine selectionKeys, columnsToKeep, colNamePairs
    for(int j = 0; j < parameters.size(); j++) {
        if(parameters[j]->getType() == "STRING") {
            selectionKeys.push_back(new ColValueKey(j, parameters[j]->toString()));
        }
        else if (parameters[j]->getType() == "ID") {
            std::pair<std::map<std::string, int>::iterator, bool> res;
            res = alreadySeenIds.insert(std::pair<std::string, int>(parameters[j]->toString(),j));
            if (res.second) {
                columnsToKeep.insert(j);
                colNamePairs.push_back(ColNamePair(int(columnsToKeep.size()) - 1, parameters[j]->toString()));
            }
            else {
                selectionKeys.push_back(new ColColKey(res.first->second, j));
            }
        }
    }
    
    Table* selectTable = getTable(predicate->getPredicateId()->toString())->select(selectionKeys);
    Table* projectTable = selectTable->project(columnsToKeep);
    Table* renameTable = projectTable->rename(colNamePairs);
    delete selectTable;
    delete projectTable;
    return renameTable;
}


void Database::processQueries() {
    std::vector<Query*> queries = datalog->getQueries()->getQueries();
    std::cout << "Query Evaluation\n";
    for(unsigned long i = 0; i < queries.size(); i++) {
        Predicate* predicate = queries[i]->getPredicate();
        std::string tableName = predicate->getPredicateId()->toString();
        std::vector<Parameter*> parameters = predicate->getParameters();
        std::vector<SelectionKey*> selectionKeys;
        std::set<int> columnsToKeep;
        std::map<std::string, int> alreadySeenIds;
        std::vector<ColNamePair> colNamePairs;
        
        // Determine selectionKeys, columnsToKeep, colNamePairs
        for(int j = 0; j < parameters.size(); j++) {
            if(parameters[j]->getType() == "STRING") {
                selectionKeys.push_back(new ColValueKey(j, parameters[j]->toString()));
            }
            else if (parameters[j]->getType() == "ID") {
                std::pair<std::map<std::string, int>::iterator, bool> res;
                res = alreadySeenIds.insert(std::pair<std::string, int>(parameters[j]->toString(),j));
                if (res.second) {
                    columnsToKeep.insert(j);
                    colNamePairs.push_back(ColNamePair(int(columnsToKeep.size()) - 1, parameters[j]->toString()));
                }
                else {
                    selectionKeys.push_back(new ColColKey(res.first->second, j));
                }
            }
        }
        
        // Create new table and select, project, and rename and print out results
        Table* selectTable = tables.find(tableName)->second->select(selectionKeys);
        Table* projectTable = selectTable->project(columnsToKeep);
        Table* queryTable = projectTable->rename(colNamePairs);
        if (i > 0) {
            std::cout << std::endl;
        }
        std::cout << tableName << "(";
        for (unsigned long i = 0; i < parameters.size(); i++) {
            std::cout << parameters[i]->toString();
            if (i < parameters.size() - 1) std::cout << ",";
        }
        std::cout << ")? ";
        if(queryTable->getRowSize() > 0) {
            std::cout << "Yes(" << queryTable->getRowSize() << ")";
        }
        else {
            std::cout << "No";
        }
        std::cout << queryTable->answerQuery();
        delete selectTable;
        delete projectTable;
        delete queryTable;
    }
}


