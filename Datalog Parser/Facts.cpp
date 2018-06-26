#include "Facts.h"

Facts::Facts(Lex* lex) {
    lex->assertToken(FACTS, true);
    lex->advance();
    lex->assertToken(COLON, true);
    lex->advance();
    while(lex->assertToken(ID, false)) {
        facts.push_back(new Fact(lex));
    }
}

std::string Facts::domainToString() {
    std::stringstream result;
    unsigned long size = facts.size();
    for (unsigned long i = 0; i < size; i++) {
        std::vector<std::string> factDomain = facts[i]->getDomain();
        for(unsigned long i = 0; i < factDomain.size(); i++) {
            domain.emplace(factDomain[i]);
        }
    }
    
    unsigned long domainSize = domain.size();
    result << "Domain(" << domainSize << "):";
    if(domainSize > 0) result << "\n";
    std::set<std::string>::iterator iter;
    for (iter = domain.begin(); iter != domain.end(); iter++) {
        result << "  " << *iter;
        if (iter != std::prev(domain.end())) result << "\n";
    }
    return result.str();
}

std::string Facts::toString() {
    std::stringstream result;
    unsigned long size = facts.size();
    result << "Facts(" << size << "):";
    if(size > 0) result << "\n";
    for(unsigned long i = 0; i < size; i++) {
        result << facts[i]->toString();
        if (i < size - 1) result << "\n";
    }
    return result.str();
}
