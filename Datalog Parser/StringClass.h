#ifndef StringClass_h
#define StringClass_h

#include "Token.h"
#include "Lex.h"
#include "Parameter.h"

class StringClass : public Parameter {
public:
    StringClass(Lex* lex)  {
        lex->assertToken(STRING, true);
        string = lex->getTop();
    }
    ~StringClass(){}
    std::string toString() {
        return string.getValue();
    }
    std::string getType() {
        return "STRING";
    }
private:
    Token string;
};

#endif /* StringClass_h */
