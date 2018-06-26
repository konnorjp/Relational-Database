#ifndef Id_h
#define Id_h

#include "Token.h"
#include "Lex.h"
#include "Parameter.h"

class Id : public Parameter {
public:
    Id(Lex* lex) {
        lex->assertToken(ID, true);
        token = lex->getTop();
    }
    ~Id() {}
    
    std::string toString() {
        return token.getValue();
    }
    std::string getType() {
        return "ID";
    }
private:
    Token token;
};

#endif /* Id_h */
