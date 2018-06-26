#ifndef Schemes_h
#define Schemes_h

#include "Scheme.h"
#include <vector>
#include <iostream>
#include "Token.h"
#include "Lex.h"

class Schemes {
public:
    Schemes(Lex* lex);
    ~Schemes() {
        for(unsigned long i = 0; i < schemes.size(); i++) {
            delete schemes[i];
        }
    }
    std::string toString();
    std::vector<Scheme*> getSchemes() { return schemes; };
private:
    std::vector<Scheme*> schemes;
};

#endif /* Schemes_h */
