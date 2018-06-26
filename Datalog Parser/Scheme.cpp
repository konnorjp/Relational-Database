#include "Scheme.h"
#include "StringClass.h"

Scheme::Scheme(Lex* lex) {
    schemeId = new Id(lex);
    lex->assertToken(LEFT_PAREN, true);
    lex->advance();
    lex->assertToken(ID, true);
    columnNames.push_back(new Id(lex));
    while(lex->assertToken(COMMA, false)) {
        lex->advance();
        lex->assertToken(ID, true);
        columnNames.push_back(new Id(lex));
    }
    lex->assertToken(RIGHT_PAREN, true);
    lex->advance();
}

std::string Scheme::toString() {
    std::stringstream result;
    unsigned long size = columnNames.size();
    result << "  " << schemeId->toString() << "(";
    for(unsigned long i = 0; i < size; i++) {
        result << columnNames[i]->toString();
        if (i < size - 1) result << ",";
    }
    result << ")";
    return result.str();
}
