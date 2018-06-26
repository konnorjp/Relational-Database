#include "Fact.h"

Fact::Fact(Lex* lex) {
    factId = new Id(lex);
    lex->assertToken(LEFT_PAREN, true);
    lex->advance();
    lex->assertToken(STRING, true);
    strings.push_back(new StringClass(lex));
    while(lex->assertToken(COMMA, false)) {
        lex->advance();
        lex->assertToken(STRING, true);
        strings.push_back(new StringClass(lex));
    }
    lex->assertToken(RIGHT_PAREN, true);
    lex->advance();
    lex->assertToken(PERIOD, true);
    lex->advance();
}

std::string Fact::toString() {
    std::stringstream result;
    unsigned long size = strings.size();
    result << "  " << factId->toString() << "(";
    for(unsigned long i = 0; i < size; i++) {
        result << strings[i]->toString();
        if (i < size - 1) result << ",";
    }
    result << ").";
    return result.str();
}

std::vector<std::string> Fact::getDomain() {
    std::vector<std::string> result;
    for(unsigned long i = 0; i < strings.size(); i++) {
        result.push_back(strings[i]->toString());
    }
    return result;
}
