#include "Queries.h"

Queries::Queries(Lex* lex) {
    lex->assertToken(QUERIES, true);
    lex->advance();
    lex->assertToken(COLON, true);
    lex->advance();
    lex->assertToken(ID, true); //Not ID but predicate
    queries.push_back(new Query(lex));
    while(lex->assertToken(ID, false)) { //Not ID but predicate
        queries.push_back(new Query(lex));
    }
    lex->assertToken(EOFILE, true);
}

std::string Queries::toString() {
    std::stringstream result;
    unsigned long size = queries.size();
    result << "Queries(" << size << "):" << "\n";
    for(unsigned long i = 0; i < size; i++) {
        result << queries[i]->toString();
        if (i < size - 1) result << "\n";
    }
    return result.str();
}
