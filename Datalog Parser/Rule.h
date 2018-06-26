#ifndef Rule_h
#define Rule_h

#include <vector>
#include <iostream>
#include "HeadPredicate.h"
#include "Predicate.h"
#include "Token.h"
#include "Lex.h"

class Rule {
public:
    Rule(Lex* lex);
    ~Rule() {
        delete head;
        for(unsigned long i = 0; i < predicates.size(); i++) {
            delete predicates[i];
        }
    }
    std::string toString();
    HeadPredicate* getHeadPredicate() { return head; };
    std::vector<Predicate*> getPredicates() { return predicates; };
private:
    HeadPredicate* head;
    std::vector<Predicate*> predicates;
};

#endif /* Rule_h */
