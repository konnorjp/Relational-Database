#include "Expression.h"

Expression::Expression(Lex* lex) {
    lex->assertToken(LEFT_PAREN, true);
    lex->advance();
    parameter1 = Parameter::createParameter(lex);
    if (lex->assertToken(ADD, false)) {
        oper = PLUS;
        lex->advance();
    }
    else {
        lex->assertToken(MULTIPLY, true);
        oper = STAR;
        lex->advance();
    }
    parameter2 = Parameter::createParameter(lex);
    lex->assertToken(RIGHT_PAREN, true);
    lex->advance();
}

std::string Expression::toString() {
    std::string operate;
    if(oper == PLUS) {
        operate = '+';
    }
    else if(oper == STAR) {
        operate = '*';
    }
    std::stringstream result;
    result << "(" << parameter1->toString() << operate;
    result << parameter2->toString() << ")";
    return result.str();
}
