#include "Rules.h"

Rules::Rules(Lex* lex) {
    lex->assertToken(RULES, true);
    lex->advance();
    lex->assertToken(COLON, true);
    lex->advance();
    while(lex->assertToken(ID, false)) {
        rules.push_back(new Rule(lex));
    }
}

std::string Rules::toString() {
    std::stringstream result;
    unsigned long size = rules.size();
    result << "Rules(" << size << "):";
    if(size > 0) result << "\n";
    for(unsigned long i = 0; i < size; i++) {
        result << rules[i]->toString();
        if (i < size - 1) result << "\n";
    }
    return result.str();
}
