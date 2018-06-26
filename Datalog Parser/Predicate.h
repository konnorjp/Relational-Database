#ifndef Predicate_h
#define Predicate_h

#include <vector>
#include "Id.h"
#include "Parameter.h"

class Predicate {
public:
    Predicate(Lex* lex);
    ~Predicate() {
        delete predicateId;
        for(unsigned long i = 0; i < parameters.size(); i++) {
            delete parameters[i];
        }
    }
    std::string toString();
    Id* getPredicateId() { return predicateId; };
    std::vector<Parameter*> getParameters() { return parameters; };
private:
    Id* predicateId;
    std::vector<Parameter*> parameters;
};

#endif /* Predicate_h */
