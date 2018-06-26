#ifndef Rules_h
#define Rules_h

#include <vector>
#include "Rule.h"
#include "Token.h"
#include "Lex.h"

class Rules {
public:
    Rules(Lex* lex);
    ~Rules() {
        for(unsigned long i = 0; i < rules.size(); i++) {
            delete rules[i];
        }
    }
    std::string toString();
    std::vector<Rule*> getRules() { return rules; };
private:
    std::vector<Rule*> rules;
};

#endif /* Rules_h */
