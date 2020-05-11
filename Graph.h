//
// Created by dimedrol on 29.04.2020.
//

#ifndef OPTIMIZATION_GRAPH_H
#define OPTIMIZATION_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

class Graph {
public:
    Graph();
    virtual ~Graph();

    //TODO: template
    class Vertex {
    private:
        std::string id;

        //TODO: вынести в DijkstraData
        double label = -1;
        Vertex* prev;

    public:
        explicit Vertex(std::string id);

    public:

        std::string getId() const {
            return id;
        }

        double getLabel() const;

        void setLabel(double label);

        void setPrevious(Vertex* v);

        Vertex* getPrevious();
    };

    void addVertex(std::string id);

    class Edge {
    protected:
        Vertex* v1;
        Vertex* v2;
        double weight;

    public:
        Edge(Vertex *v1, Vertex *v2, double weight);

        const Vertex* get_v1() { return v1; }
        const Vertex* get_v2() { return v2; }

        double getWeight() const;

        //TODO: make private if need
        Vertex* getSecond(const Vertex* v) {
            if (v1 != v && v2 != v)
                return nullptr;
            else if (v1 == v)
                return v2;
            else if (v2 == v)
                return v1;
        } //TODO: rename
    };

    class Path {
        //list of edges, guarantees coherence
    private:
        std::list<Edge*> edges;

    public:
        void addNextEdge(Edge*);

        std::string to_string() const;

        double getSummaryDistance() const {
            double result = 0;
            for (auto edge: edges)
                result += edge->getWeight();
            return result;
        }

        bool empty() const {
            return edges.empty();
        }
    };

    virtual void addEdge(std::string id1, std::string id2, double weight);
    double getWeightByVertices(Vertex* v1, Vertex* v2);

    std::vector<Vertex*> getAdjacent(Vertex* vertex);
    Path Dijkstra(const std::string& startID, const std::string& endID);


protected:
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
};

//class Graph {
//public:
//    class Vertex {
//        std::string id;
//
//    public:
//        Vertex(const std::string &id);
//        std::string getId() const {
//            return id;
//        }
//
////        bool operator==(const Vertex& vertex) {
////            return this->id == vertex.id;
////        }
//
//        class Hasher {
//        public:
//            std::size_t operator()(const Vertex& vertex) const
//            {
//                using std::size_t;
//                using std::hash;
//                using std::string;
//
//                return ((hash<string>()(vertex.id)));
//            }
//        };
//    };
//
//    friend bool operator==(const Vertex& vertex1, const Vertex& vertex2) {
//        return vertex1.getId() == vertex2.getId(); //что с хешами, если возвращают копию?
//    }
//
//    class Edge {
//        Graph::Vertex v1;
//        Graph::Vertex v2;
//        double distance;
//        double pheromone;
//
//    public:
//        Edge(const Graph::Vertex &v1, const Graph::Vertex &v2, double distance);
//        std::string getId1() const {
//            return v1.getId();
//        }
//        std::string getId2() const {
//            return v2.getId();
//        }
//
//        Graph::Vertex getVertex1() {
//            return v1;
//        };
//
//        Graph::Vertex getVertex2() {
//            return v2;
//        };
//
//        double getDistance() {
//            return distance;
//        }
//
//        double getPheromone() {
//            return pheromone;
//        }
//
//        void setPheromone(double pheromone) {
//            this->pheromone = pheromone;
//        }
//
//        class Hasher {
//        public:
//            std::size_t operator()(const Edge& edge) const
//            {
//                using std::size_t;
//                using std::hash;
//                using std::string;
//
//                return ((hash<string>()(edge.v1.getId())) ^ (hash<string>()(edge.v2.getId()) << 1) >> 1);
//            }
//        };
//    };
//
//    friend bool operator==(const Edge& edge1, const Edge& edge2) {
//        return
//        ((edge1.getId1() == edge2.getId1() && edge1.getId2() == edge2.getId2()) ||
//                (edge1.getId1() == edge2.getId2() && edge1.getId2() == edge2.getId1()));
//    }
//
//    void addVertex(std::string id);
//    void addEdge(std::string id1, std::string id2, double distance);
//    Edge getEdge(std::string id1, std::string id2);
//    //std::set<std::string> getAdjacent(std::string vertex_id);
//    std::unordered_set<Vertex, Vertex::Hasher> getAdjacent(Vertex vertex);
//    std::vector<Vertex> getVertices();
//    static double calculateDistance(std::vector<Graph::Edge> edges);
//
//    void vaporize(double pheromone_evaporation) {
//        for (Edge edge: edges) {
//            edge.setPheromone(edge.getPheromone() * (1 - pheromone_evaporation));
//        }
//    }
//
//private:
//    std::unordered_set<Vertex, Vertex::Hasher> vertices;
//    std::unordered_set<Edge, Edge::Hasher> edges;
//};


#endif //OPTIMIZATION_GRAPH_H
