#include "Datalog.h"

Datalog::Datalog(char* filename) {
    Lex* lex = new Lex(filename);
    schemes = new Schemes(lex);
    facts = new Facts(lex);
    rules = new Rules(lex);
    queries = new Queries(lex);
    graph = new Graph(rules, queries);
    //createOptimizedRules();
    graph->printGraph();
    //graph->printInvertedGraph();
    //graph->printTO();
    //graph->printSCC();
    delete lex;
}

std::string Datalog::toString() {
    return schemes->toString() + '\n' +
        facts->toString() + '\n' +
        rules->toString() + '\n' +
        queries->toString() + '\n' +
        facts->domainToString();
}

/*void Datalog::createOptimizedRules() {
    std::vector<std::vector<int>> SCC = graph->getSCC();
    std::map<int, Rule*> ruleMapping = graph->getRuleMapping();
    for(unsigned long i = 0; i < SCC.size(); i++) {
        std::vector<Rule*> ruleVector;
        for(unsigned long j = 0; j < SCC[i].size(); j++) {
            ruleVector.push_back(ruleMapping[SCC[i][j]]);
        }
        optimizedRules.push_back(ruleVector);
    }
}*/
