#include "Graph.h"

Graph::Graph(Rules* rulesObj, Queries* queries) {
    //Create a mapping to all the rules and don't include the rules that aren't needed
    std::vector<Rule*> rules = rulesObj->getRules();
    /*std::set<std::string> queryIds;
    for(unsigned long i = 0; i < queries->getQueries().size(); i++) {
        queryIds.insert(queries->getQueries()[i]->getPredicate()->getPredicateId()->toString());
    }*/
    for(unsigned long i = 0; i < rules.size(); i++) {
        /*if(queryIds.count(rules[i]->getHeadPredicate()->getHeadId()->toString())) {
            ruleMapping.insert(std::pair<int,Rule*>(int(i),rules[i]));
        }*/
        ruleMapping.insert(std::pair<int,Rule*>(int(i),rules[i]));
    }
    
    //Create dependencyGraph and invertedGraph
    createGraphs();
    
    //Create topologicalOrdering
    createTopologicalOrdering();
    
    //Produce Strongly Connected Components
    createStronglyConnectedComponents();
}

void Graph::createStronglyConnectedComponents() {
    while(!topologicalOrdering.empty()) {
        std::vector<int> SCC;
        std::map<int, std::set<int>>::iterator iter = graph.find(topologicalOrdering.top());
        recurseGraph(iter, SCC);
        while(!topologicalOrdering.empty() && visitedToCreateSCC.count(topologicalOrdering.top())) {
            SCC.push_back(topologicalOrdering.top());
            topologicalOrdering.pop();
        }
        stronglyConnectedComponents.push_back(SCC);
    }
}

void Graph::recurseGraph(std::map<int, std::set<int>>::iterator iter, std::vector<int> &SCC) {
    visitedToCreateSCC.insert(iter->first);
    if(iter->second.empty()) {
        SCC.push_back(topologicalOrdering.top());
        topologicalOrdering.pop();
        return;
    }
    std::set<int>::iterator iterSet;
    for(iterSet = iter->second.begin(); iterSet != iter->second.end(); iterSet++) {
        std::map<int, std::set<int>>::iterator it;
        it = graph.find(*iterSet);
        if(!visitedToCreateSCC.count(it->first)) {
            recurseGraph(it, SCC);
        }
    }
}

void Graph::createTopologicalOrdering() {
    std::map<int, std::set<int>>::iterator iter;
    for(iter = invertedGraph.begin(); iter != invertedGraph.end(); iter++) {
        if(!visitedToCreateTO.count(iter->first)) {
            recurseInvertedGraph(iter);
            topologicalOrdering.push(iter->first);
        }
    }
}

void Graph::recurseInvertedGraph(std::map<int, std::set<int>>::iterator iter) {
    if(visitedToCreateTO.count(iter->first)) {
        return;
    }
    visitedToCreateTO.insert(iter->first);
    std::set<int>::iterator iterSet;
    for(iterSet = iter->second.begin(); iterSet != iter->second.end(); iterSet++) {
        std::map<int, std::set<int>>::iterator it;
        it = invertedGraph.find(*iterSet);
        if(!visitedToCreateTO.count(it->first)) {
            recurseInvertedGraph(it);
            topologicalOrdering.push(it->first);
        }
    }
}

void Graph::createGraphs() {
    std::map<int, Rule*>::iterator iter;
    std::map<int, Rule*>::iterator itr;
    for(iter = ruleMapping.begin(); iter != ruleMapping.end(); iter++) {
        std::set<int> rulePredicatesInMap;
        std::vector<Predicate*> predicates = iter->second->getPredicates();
        for(unsigned long i = 0; i < predicates.size(); i++) {
            for(itr = ruleMapping.begin(); itr != ruleMapping.end(); itr++) {
                std::string predicateValue = predicates[i]->getPredicateId()->toString();
                std::string ruleValue = itr->second->getHeadPredicate()->getHeadId()->toString();
                std::set<int> invertSet;
                if(predicateValue == ruleValue) {
                    rulePredicatesInMap.insert(itr->first);
                    std::map<int, std::set<int>>::iterator iterInvert = invertedGraph.find(itr->first);
                    if(iterInvert != invertedGraph.end()) {
                        iterInvert->second.insert(iter->first);
                    }
                    else {
                        invertSet.insert(iter->first);
                    }
                }
                invertedGraph.insert(std::pair<int,std::set<int>>(itr->first,invertSet));
            }
        }
        graph.insert(std::pair<int,std::set<int>>(iter->first,rulePredicatesInMap));
    }
}

void Graph::printGraph() {
    std::map<int, std::set<int>>::iterator iter;
    std::set<int>::iterator iterSet;
    std::cout << "Dependency Graph\n";
    for(iter = graph.begin(); iter != graph.end(); iter++) {
        std::cout << "R" << iter->first << ":";
        int count = 0;
        int setSize = int(iter->second.size());
        for (iterSet = iter->second.begin(); iterSet != iter->second.end(); iterSet++) {
            if(count < setSize - 1) std::cout << "R" << *iterSet << ",";
            else std::cout << "R" << *iterSet;
            count++;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Graph::printInvertedGraph() {
    std::map<int, std::set<int>>::iterator iter;
    std::set<int>::iterator iterSet;
    for(iter = invertedGraph.begin(); iter != invertedGraph.end(); iter++) {
        std::cout << iter->first << ":";
        int count = 0;
        int setSize = int(iter->second.size());
        for (iterSet = iter->second.begin(); iterSet != iter->second.end(); iterSet++) {
            if(count < setSize - 1) std::cout << *iterSet << ",";
            else std::cout << *iterSet;
            count++;
        }
        std::cout << "\n";
    }
}

void Graph::printTO() {
    
    while (!topologicalOrdering.empty())
    {
        std::cout << "Help";
        std::cout << ' ' << topologicalOrdering.top();
        topologicalOrdering.pop();
    }
    std::cout << '\n';
}

void Graph::printSCC() {
    for(unsigned long i = 0; i < stronglyConnectedComponents.size(); i++) {
        std::cout << "{";
        for(unsigned long j = 0; j < stronglyConnectedComponents[i].size(); j++) {
            std::cout << stronglyConnectedComponents[i][j];
            if(j < stronglyConnectedComponents[i].size() - 1) std::cout << ",";
        }
        std::cout << "}\n";
    }
}

