#ifndef Queries_h
#define Queries_h

#include <vector>
#include "Query.h"
#include "Token.h"
#include "Lex.h"

class Queries {
public:
    Queries(Lex* lex);
    ~Queries() {
        for(unsigned long i = 0; i < queries.size(); i++) {
            delete queries[i];
        }
    }
    std::string toString();
    std::vector<Query*> getQueries() { return queries; };
private:
    std::vector<Query*> queries;
};

#endif /* Queries_h */
