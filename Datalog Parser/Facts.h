#ifndef Facts_h
#define Facts_h

#include <vector>
#include <iostream>
#include <set>
#include "Fact.h"
#include "Token.h"
#include "Lex.h"

class Facts {
public:
    Facts(Lex* lex);
    ~Facts() {
        for(unsigned long i = 0; i < facts.size(); i++) {
            delete facts[i];
        }
    }
    std::string toString();
    std::string domainToString();
    std::vector<Fact*> getFacts() { return facts; };
private:
    std::vector<Fact*> facts;
    std::set<std::string> domain;
};

#endif /* Facts_h */
