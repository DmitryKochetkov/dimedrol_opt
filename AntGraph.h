//
// Created by dimedrol on 10.05.2020.
//

#ifndef OPTIMIZATION_ANTGRAPH_H
#define OPTIMIZATION_ANTGRAPH_H


#include "Graph.h"

class AntGraph: public Graph {

public:
    AntGraph() : Graph() {}

    class Edge: public Graph::Edge {
    private:
        double pheromone;
    public:
        Edge(Vertex *v1, Vertex *v2, double weight, double pheromone) : Graph::Edge(v1, v2, weight), pheromone(pheromone) {}

        double getPheromone() const {
            return pheromone;
        }

        void setPheromone(double pheromone) {
            this->pheromone = pheromone;
        }
    };



private:

public:
    void vaporize(double pheromone_evaporation) {
        for (Graph::Edge* edge: edges) {
            ((AntGraph::Edge*)edge)->setPheromone(((AntGraph::Edge*)edge)->getPheromone() * (1 - pheromone_evaporation));
        }
    }

    void addEdge(std::string id1, std::string id2, double weight) override {
        Vertex* v1 = nullptr;
        Vertex* v2 = nullptr;
        for (Vertex* vertex: vertices) {
            if (vertex->getId() == id1)
                v1 = vertex;
            else if (vertex->getId() == id2)
                v2 = vertex;
        }

        if (v1 == nullptr)
        {
            std::cout << "GRAPH (" << this << ") Cannot add edge: vertex with id " + id1 + " doesn't exists." << std::endl;
            return;
        }

        if (v2 == nullptr)
        {
            std::cout << "GRAPH (" << this << ") Cannot add edge: vertex with id " + id2 + " doesn't exists." << std::endl;
            return;
        }

        Edge* edge = new Edge(v1, v2, weight, 0.003);
        edges.push_back(edge);
    }

    //bad functions

    std::vector<Vertex*> getVertices() {
        return Graph::vertices;
    }

    Edge* getEdge(std::string s1, std::string s2) {
        for (auto edge: edges)
            if (((edge->get_v1()->getId() == s1) && (edge->get_v2()->getId() == s2)) ||
                ((edge->get_v1()->getId() == s2) && (edge->get_v2()->getId() == s1)))
                return ((AntGraph::Edge*)edge);
        return nullptr;
    }
};


#endif //OPTIMIZATION_ANTGRAPH_H
