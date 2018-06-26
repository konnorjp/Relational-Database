#include "Table.h"
#include "Database.h"
#include "Datalog.h"
#include "Rules.h"

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc ; i++) {
        try{
            Database* database = new Database(argv[i]);
            database->processOptimizedRules();
            database->processQueries();
            //std::cout << "Success!\n";
            delete database;
        } catch(Token token) {
            std::cout << "Failure!\n  " << token.print();
        }
    }
    return 0;
}

