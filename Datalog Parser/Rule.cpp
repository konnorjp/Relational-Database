#include "Rule.h"

Rule::Rule(Lex* lex) {
    head = new HeadPredicate(lex);
    lex->assertToken(COLON_DASH, true);
    lex->advance();
    predicates.push_back(new Predicate(lex));
    while(!lex->assertToken(PERIOD, false)) {
        lex->assertToken(COMMA, true);
        lex->advance();
        predicates.push_back(new Predicate(lex));
    }
    lex->assertToken(PERIOD, true);
    lex->advance();
}

std::string Rule::toString() {
    std::stringstream result;
    unsigned long size = predicates.size();
    result << "  " << head->toString() << " :- ";
    for(unsigned long i = 0; i < size; i++) {
        result << predicates[i]->toString();
        if (i < size - 1) result << ",";
    }
    result << ".";
    return result.str();
}



