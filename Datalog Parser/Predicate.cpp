#include "Predicate.h"

Predicate::Predicate(Lex* lex) {
    predicateId = new Id(lex);
    lex->assertToken(LEFT_PAREN, true);
    lex->advance();
    parameters.push_back(Parameter::createParameter(lex));
    while(!lex->assertToken(RIGHT_PAREN, false)) {
        lex->assertToken(COMMA, true);
        lex->advance();
        parameters.push_back(Parameter::createParameter(lex));
    }
    lex->assertToken(RIGHT_PAREN, true);
    lex->advance();
}

std::string Predicate::toString() {
    std::stringstream result;
    unsigned long size = parameters.size();
    result << predicateId->toString() << "(";
    for(unsigned long i = 0; i < size; i++) {
        result << parameters[i]->toString();
        if (i < size - 1) result << ",";
    }
    result << ")";
    return result.str();
}
