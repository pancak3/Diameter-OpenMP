#include <vector>
#include "iostream"

using namespace std;
using std::cin;
using std::cout;

struct Edge {
    int fromVertex, toVertex, edgeNum, weight;
    struct Edge *next;
};

struct Vertex {
    int vertexNum;
    struct Edge *next;
};

class DirectedGraph {
public:
    ~DirectedGraph();

    void init();

    void print();

private:
    int vertexCount, edgeCount;
    Vertex *vertexList;
};

DirectedGraph::~DirectedGraph() {
    for (int i = 0; i < vertexCount; i++) {
        Edge *tmpEdge = vertexList[i].next;
        Edge *currentEdge = NULL;
        while (tmpEdge) {
            currentEdge = tmpEdge;
            tmpEdge = tmpEdge->next;
            delete currentEdge;
        }
    }
    delete[] vertexList;
}

void DirectedGraph::init() {
    cin >> vertexCount;
    cin >> edgeCount;
    vertexList = new Vertex[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        vertexList[i].vertexNum = i;
        vertexList[i].next = NULL;
    }
    for (int i = 0; i < edgeCount; i++) {
        Edge *tmpEdge = new Edge();
        cin >> tmpEdge->fromVertex;
        cin >> tmpEdge->toVertex;
        cin >> tmpEdge->weight;
        tmpEdge->next = NULL;
        if (vertexList[tmpEdge->fromVertex].next) {
            Edge *nextEdge = vertexList[tmpEdge->fromVertex].next;
            while (nextEdge->next) {
                nextEdge = nextEdge->next;
            }
            nextEdge->next = tmpEdge;
        } else {
            vertexList[tmpEdge->fromVertex].next = tmpEdge;
        }
    }
}

void DirectedGraph::print() {
    for (int i = 0; i < vertexCount; i++) {

    }
    for (int i = 0; i < vertexCount; ++i) {
        Edge *tmpEdge = vertexList[i].next;
        cout << "vertex:" << vertexList[i].vertexNum;
        while (tmpEdge) {
            cout << "->" << tmpEdge->toVertex;
            cout << "(w:" << tmpEdge->weight << ")";
            tmpEdge = tmpEdge->next;
        }
        cout << "->NULL" << endl;
    }
}

int main() {
    DirectedGraph graph{};
    graph.init();
    graph.print();
    return 0;

}