#ifndef Expression_h
#define Expression_h

#include "Parameter.h"
#include "Token.h"
#include "Lex.h"
#include <iostream>

enum OperatorType { PLUS, STAR };

class Expression : public Parameter {
public:
    Expression(Lex* lex);
    ~Expression() {
        delete parameter1;
        delete parameter2;
    }
    std::string getType() { return "EXPRESSION"; };
    std::string toString();
    Parameter* getParameter1() { return parameter1; };
    char getOperatorType() {
        if(oper == PLUS) {
            return '+';
        }
        else {
            return '*';
        }
    }
    Parameter* getParameter2() { return parameter2; };
private:
    Parameter* parameter1;
    OperatorType oper;
    Parameter* parameter2;
};

#endif /* Expression_h */
