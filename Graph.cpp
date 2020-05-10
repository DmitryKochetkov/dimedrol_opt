//
// Created by dimedrol on 29.04.2020.
//

#include "Graph.h"
#include <algorithm>

Graph::Vertex::Vertex(std::string id) {
    this->id = id;
}

double Graph::Vertex::getLabel() const {
    return label;
}

void Graph::Vertex::setLabel(double label) {
    Vertex::label = label;
}

Graph::Vertex* Graph::Vertex::getPrevious() {
    return prev;
}

void Graph::Vertex::setPrevious(Graph::Vertex* vertex) {
    this->prev = vertex;
}

void Graph::addVertex(std::string id) {
    for (Vertex* vertex: vertices)
        if (vertex->getId() == id)
        {
            std::cout << "GRAPH (" << this << ") Warning: vertex with id " + id + " already exists." << std::endl;
            return;
        }

    //why use emplace_back()?
    vertices.push_back(new Vertex(id));
}

Graph::Graph() = default;

Graph::~Graph() {
    for (Vertex* vertex: vertices)
        delete vertex;
}

Graph::Edge::Edge(Graph::Vertex *v1, Graph::Vertex *v2, double weight) : v1(v1), v2(v2), weight(weight) {}

double Graph::Edge::getWeight() const {
    return weight;
}

void Graph::addEdge(std::string id1, std::string id2, double weight) {
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

    Edge* edge = new Edge(v1, v2, weight);
    edges.push_back(edge);
}

std::vector<Graph::Vertex *> Graph::getAdjacent(Graph::Vertex *vertex) {
    std::vector<Vertex*> adjacent;
    for (Edge* edge: edges) {
        Vertex* v2 = edge->getSecond(vertex); //TODO: rename getSecond
        if (v2 != nullptr)
            adjacent.push_back(v2);
    }
    return adjacent;
}

double Graph::getWeightByVertices(Vertex* v1, Vertex* v2) {
    Edge* key = nullptr;
    for (Edge* edge: edges) {
        if (edge->getSecond(v1) == v2)
            key = edge;
    }

    if (key == nullptr)
        throw std::runtime_error("Graph: there is no edge between " + v1->getId() + " and " + v2->getId()); //TODO: print graph address
    return key->getWeight();
}

Graph::Path Graph::Dijkstra(const std::string &startID, const std::string &endID) {
    Vertex* start = nullptr;
    Vertex* end = nullptr;

    for (Vertex* vertex: vertices) {
        if (vertex->getId() == startID)
            start = vertex;
        if (vertex->getId() == endID)
            end = vertex;

        if (start != nullptr && end != nullptr)
            break;
    }

    std::vector<Vertex*> unvisited = vertices;
    start->setLabel(0);
    Vertex* current = start;
    Vertex* next = nullptr;

    while (std::find(unvisited.begin(), unvisited.end(), end) != unvisited.end()) {
        for (Vertex* vertex: getAdjacent(current)) {
            double newLabel = current->getLabel() + getWeightByVertices(current, vertex);
            if (vertex->getLabel() < 0 || newLabel < vertex->getLabel()) {
                vertex->setLabel(newLabel);
                vertex->setPrevious(current);
            }
        }

        //текущая вершина посещена, удаляем из unvisited
        std::vector<Vertex*>::iterator toRemove;
        for (auto iter = unvisited.begin(); iter != unvisited.end(); iter++) {
            if (*iter == current) {
                toRemove = iter;
                break;
            }
        }

        unvisited.erase(toRemove);

        //next - вершина с наименьшей меткой
        for (Vertex* vertex: unvisited) {
            if (next == nullptr || (vertex->getLabel() > 0 && vertex->getLabel() < next->getLabel()))
                next = vertex;
        }

        current = next;
        next = nullptr;
    }

    std::list<Edge*> reversed;
    for (Vertex* vertex = end; vertex != start; vertex = vertex->getPrevious()) {
        for (Edge* edge: edges)
            if (edge->getSecond(vertex) == vertex->getPrevious()) {
                reversed.push_front(edge);
                break;
            }
    }

    Graph::Path path;
    for (Edge* edge: reversed)
        path.addNextEdge(edge);
    return path;
}

std::string Graph::Path::to_string() const {
    if (this->edges.empty())
        return "empty path";

    std::string result;
    for (auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
        result += (*iter)->get_v1()->getId() + " -> ";
    result += this->edges.back()->get_v2()->getId();
    return result;
}

void Graph::Path::addNextEdge(Graph::Edge* edge) {
    if (!this->edges.empty() && this->edges.back()->getSecond(edge->get_v1()) == nullptr && this->edges.back()->getSecond(edge->get_v2()) == nullptr) {
        std::cout << "WARNING Graph::addNextEdge: edge is not coherent" << std::endl;
        return;
    }

    this->edges.push_back(edge);
}

//Graph::Vertex::Vertex(const std::string &id) : id(id) {}
//
//void Graph::addVertex(std::string id) {
//    for (Vertex vertex: vertices)
//        if (vertex.getId() == id)
//            return; //TODO: throw exception
//    vertices.insert(Vertex(id));
//}
//
//void Graph::addEdge(std::string id1, std::string id2, double weight) {
//    for (Edge edge: edges)
//        if ((edge.getId1() == id1 && edge.getId2() == id2) || (edge.getId2() == id1 && edge.getId1() == id2))
//            return; //TODO: throw exception
//    edges.insert(Edge(id1, id2, weight));
//}
//
//std::unordered_set<Graph::Vertex, Graph::Vertex::Hasher> Graph::getAdjacent(Graph::Vertex vertex) {
//    std::unordered_set<Graph::Vertex, Graph::Vertex::Hasher> adjacent;
//    for (Edge edge: edges) {
//        if (edge.getId1() == vertex.getId())
//            adjacent.insert(edge.getVertex2());
//        else if (edge.getId2() == vertex.getId())
//            adjacent.insert(edge.getVertex1());
//    }
//    return adjacent;
//}
//
////std::set<std::string> Graph::getAdjacent(std::string key_id) {
////    for (Vertex vertex: vertices)
////        if (vertex.getId() == key_id)
////            return getAdjacent(vertex);
////    throw std::runtime_error("Graph::getAdjacent - Key not found");
////}
//
//Graph::Edge Graph::getEdge(std::string id1, std::string id2) {
//    for (Edge edge: edges) {
//        if ((edge.getId1() == id1 && edge.getId2() == id2) || (edge.getId2() == id1 && edge.getId1() == id2))
//            return edge;
//    }
//}
//
//std::vector<Graph::Vertex> Graph::getVertices() {
//    std::vector<Graph::Vertex> result;
//    for (Vertex vertex: vertices)
//        result.push_back(vertex.getId());
//    return result;
//}
//
//double Graph::calculateDistance(std::vector<Graph::Edge> edges) {
//    double res = 0;
//    for (Graph::Edge edge: edges)
//        res += edge.getDistance();
//    return res;
//}
//
//Graph::Edge::Edge(const Graph::Vertex &v1, const Graph::Vertex &v2, double distance) : v1(v1), v2(v2), distance(distance) {
//    pheromone = get_random(0.0, 0.001); //инициализация малыми значениями феромона
//}
