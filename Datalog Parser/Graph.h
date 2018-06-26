#ifndef Graph_h
#define Graph_h

#include "Rules.h"
#include "Queries.h"
#include <map>
#include <set>
#include <stack>
#include <vector>

class Graph {
public:
    Graph(Rules* rulesObj, Queries* queriesObj);
    ~Graph() {};
    std::vector<std::vector<int>> getSCC() {
        return stronglyConnectedComponents;
    }
    std::map<int, Rule*> getRuleMapping(){
        return ruleMapping;
    }
    std::map<int,std::set<int>> getGraph() {
        return graph;
    }
    void printTopologicalOrdering();
    void printGraph();
    void printInvertedGraph();
    void printTO();
    void printSCC();
private:
    std::map<int,std::set<int>> graph;
    std::map<int,std::set<int>> invertedGraph;
    std::map<int, Rule*> ruleMapping;
    std::stack<int> topologicalOrdering;
    std::set<int> visitedToCreateTO;
    std::set<int> visitedToCreateSCC;
    std::vector<std::vector<int>> stronglyConnectedComponents;
    void recurseInvertedGraph(std::map<int, std::set<int>>::iterator iter);
    void recurseGraph(std::map<int, std::set<int>>::iterator iter, std::vector<int> &SCC);
    void createTopologicalOrdering();
    void createGraphs();
    void createStronglyConnectedComponents();
};

#endif /* Graph_h */
