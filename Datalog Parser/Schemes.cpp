#include "Schemes.h"
#include "StringClass.h"

Schemes::Schemes(Lex* lex) {
    lex->assertToken(SCHEMES, true);
    lex->advance();
    lex->assertToken(COLON, true);
    lex->advance();
    lex->assertToken(ID, true);
    schemes.push_back(new Scheme(lex));
    while(lex->assertToken(ID, false)) {
        schemes.push_back(new Scheme(lex));
    }
}

std::string Schemes::toString() {
    std::stringstream result;
    unsigned long size = schemes.size();
    result << "Schemes(" << size << "):" << "\n";
    for(unsigned long i = 0; i < size; i++) {
        result << schemes[i]->toString();
        if (i < size - 1) result << "\n";
    }
    return result.str();
}
