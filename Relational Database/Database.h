#ifndef Database_h
#define Database_h

#include <map>
#include "Table.h"
#include "Datalog.h"

class Database {
public:
    Database(char* filename);
    ~Database(){
        delete datalog;
        std::map<std::string, Table*>::iterator iter;
        for(iter = tables.begin(); iter != tables.end(); iter++) {
            delete iter->second;
        }
    }
    std::map<std::string, Table*> getTables() {
        return tables;
    }
    Table* getTable(std::string tableName) {
        return tables[tableName];
    }
    void processRules();
    void processOptimizedRules();
    void processQueries();
    
private:
    std::map<std::string, Table*> tables;
    Datalog* datalog;
    int timesProcessRules;
    bool nothingChanged = true;
    void processRule(Rule* rule);
    Table* processPredicate(Predicate* predicate);
};

#endif /* Database_h */
