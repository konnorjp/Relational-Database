#ifndef Datalog_h
#define Datalog_h

#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "Lex.h"
#include "Token.h"
#include "Graph.h"
#include <vector>
#include <iostream>

class Datalog {
public:
    Datalog(char* filename);
    ~Datalog() {
        delete schemes;
        delete facts;
        delete rules;
        delete queries;
    }
    
    std::string toString();
    Schemes* getSchemes() { return schemes; };
    Facts* getFacts() { return facts; };
    Rules* getRules() { return rules; };
    Queries* getQueries() { return queries; };
    std::vector<std::vector<int>> getSCC() {
        return graph->getSCC();
    }
    std::map<int, Rule*> getRuleMapping() {
        return graph->getRuleMapping();
    }
    std::map<int,std::set<int>> getGraph() {
        return graph->getGraph();
    }
    /*std::vector<std::vector<Rule*>> getOptimizedRules() {
        return optimizedRules;
    }*/
private:
    Schemes* schemes;
    Facts* facts;
    Rules* rules;
    Queries* queries;
    Graph* graph;
    //std::vector<std::vector<Rule*>> optimizedRules;
    //void createOptimizedRules();
};

#endif /* Datalog_h */
