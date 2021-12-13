#include <iostream>
#include <iomanip>
#include <algorithm>

#include "graph.hpp"

Graph::Graph(/* args */) {
}

Graph::~Graph() {
}

int Graph::getPathsSize() {
    return paths.size();
}

int Graph::addNode(std::string node) {

    for (size_t i = 0; i < nodes.size(); i++) {
        if ( node == nodes[i] ) return i;
    }

    nodes.push_back(node); adj.push_back({});
    size.push_back( (islower(node[0])) ? small : large );
    return nodes.size()-1;
}

void Graph::addEdge(int node, int neighbor) {
    adj[node].push_back(neighbor);
    adj[neighbor].push_back(node);
}

void Graph::print() {
    std::cout << "Adjacents:" << std::endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << "\033[0;35m" << std::setw(5) << std::left << nodes[i] << "\033[0m \033[0;37m{\033[0m ";
        for (auto v : adj[i]) {
            if ( v != adj[i][0] ) {
                std::cout << "\033[0;37m,\033[0m ";
            }
            std::cout << "\033[0;36m" << nodes[v] << "\033[0m";
        }
        std::cout << " \033[0;37m}\033[0m" << std::endl;
    }
}

void Graph::clearPaths() {
    for (size_t i = 0; i < paths.size(); i++) {
        paths[i].clear();
    }
    paths.clear();
}

void Graph::printPaths() {
    int start = addNode("start");
    std::cout << "Paths:" << std::endl;
    for (auto path : paths) {
        for (auto v : path) {
            if ( v != start ) {
                std::cout << " \033[0;37m>\033[0m ";
            }
            std::cout << "\033[0;33m" << nodes[v] << "\033[0m";
        }
        std::cout << std::endl;
    }
}

/* Functions for part 1 */

void Graph::findPaths_1(int x, int y) {
    
    clearPaths();

    std::vector<int> path;
    std::vector<int> visit (nodes.size(),0);

    findPath_1(x,y,path,visit);
}

void Graph::findPath_1(int x, int y, std::vector<int> path, std::vector<int> visit) {

    if ( x == y ) {
        paths.push_back(path);
        return;
    }

    if ( size[x] == small && visit[x] > 0 ) {
        return;
    }
            
    path.push_back(x);
    visit[x]++;


    for (auto pos : adj[x] ) {
        findPath_1(pos,y,path,visit);
    }

}

/* Functions for part 1 */

void Graph::findPaths_2(int x, int y) {
    
    clearPaths();

    std::vector<int> path;
    std::vector<int> visit (nodes.size(),0);

    findPath_2(x,y,path,visit);
}

void Graph::findPath_2(int x, int y, std::vector<int> path, std::vector<int> visit) {

    if ( x == y ) {
        paths.push_back(path);
        return;
    }

    if ( x == addNode("start") && visit[x] > 0 ) { return; }

    if ( size[x] == small && visit[x] > 0 ) {
        bool doubleVisitedExists = false;
        for (int i = 0; i < visit.size(); i++) {
            if ( size[i] == small && visit[i] > 1 ) doubleVisitedExists = true;
        }
        if ( doubleVisitedExists ) {
            return;
        }
    }
            
    path.push_back(x);
    visit[x]++;


    for (auto pos : adj[x] ) {
        findPath_2(pos,y,path,visit);
    }

}