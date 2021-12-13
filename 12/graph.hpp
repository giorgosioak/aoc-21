#include <vector>
#include <string>

enum cave {small, large};

class Graph {
    private:
        std::vector<std::vector<int>> adj;
        std::vector<std::vector<int>> paths;
        std::vector<std::string> nodes;
        std::vector<cave> size;
    public:
        Graph(/* args */);
        ~Graph();
        int getPathsSize();
        int addNode(std::string node);
        void addEdge(int node, int neighbor);
        void print();
        void clearPaths();
        void printPaths();
        void findPaths_1(int origin, int destination);
        void findPath_1(int position, int destination, std::vector<int> path, std::vector<int> visit);
        void findPaths_2(int origin, int destination);
        void findPath_2(int position, int destination, std::vector<int> path, std::vector<int> visit);
};