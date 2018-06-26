#include "HeadPredicate.h"

HeadPredicate::HeadPredicate(Lex* lex) {
    headId = new Id(lex);
    lex->assertToken(LEFT_PAREN, true);
    lex->advance();
    ids.push_back(new Id(lex));
    while(lex->assertToken(COMMA, false)) {
        lex->advance();
        ids.push_back(new Id(lex));
    }
    lex->assertToken(RIGHT_PAREN, true);
    lex->advance();
}

std::string HeadPredicate::toString() {
    std::stringstream result;
    unsigned long size = ids.size();
    result << headId->toString() << "(";
    for(unsigned long i = 0; i < size; i++) {
        result << ids[i]->toString();
        if (i < size - 1) result << ",";
    }
    result << ")";
    return result.str();
}
