#ifndef Fact_h
#define Fact_h

#include <vector>
#include "Id.h"
#include "StringClass.h"
#include "Token.h"
#include "Lex.h"

class Fact {
public:
    Fact(Lex* lex);
    ~Fact() {
        for(unsigned long i = 0; i < strings.size(); i++) {
            delete strings[i];
        }
    }
    std::string toString();
    std::vector<std::string> getDomain();
    Id* getFactId() { return factId; };
    std::vector<StringClass*> getStrings() { return strings; };
private:
    Id* factId;
    std::vector<StringClass*> strings;
};

#endif /* Fact_h */
