//
// Created by dimedrol on 29.04.2020.
//

#ifndef OPTIMIZATION_ANTCOLONY_H
#define OPTIMIZATION_ANTCOLONY_H

#include <string>
//#include <list>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "Graph.h"
#include "QuickRandom.h"
#include "AntGraph.h"

class AntColony {
public:
    class Ant {
        std::vector<Graph::Vertex*> visited; //список пройденных узлов (табу)
        Graph::Vertex* start;

    public:
        Ant(Graph::Vertex* start): start(start) {}

        Graph::Vertex* getCurrentLocation() {
            return visited.back(); //текущее местоположение - последняя вершина в списке узлов
        }

        Graph::Path * nextIteration(AntColony& antColony);
    };

private:
    AntGraph graph;
    std::vector<Ant> ants;
    double distance_importance; //важность расстояния (степень)
    double pheromone_importance; //важность феромона (степень)
    double pheromone_multiplier; //коэффициент к обратной пропорциональности в обновлении феромона
    double pheromone_evaporation; //скорость испарения феромона

public:

    AntColony(AntGraph &graph, size_t size,
            double distance_importance, double pheromone_importance, double pheromone_multiplier, double pheromone_evaporation) : graph(graph) {
        this->distance_importance = distance_importance;
        this->pheromone_importance = pheromone_importance;
        this->pheromone_multiplier = pheromone_multiplier;
        this->pheromone_evaporation = pheromone_evaporation;

        //равномерное распределение муравьев по вершинам графа
        for (Graph::Vertex* vertex: graph.getVertices()) {
            for (int i = 0; i < size / graph.getVertices().size(); i++)
                ants.push_back(Ant(vertex));
        }
    }

    AntGraph::Path* findOptimalPath(size_t iterations) {
        //TODO: переинцициализировать муравьев для многократного вызова
        AntGraph::Path* path = nullptr;

        for (Ant ant: ants) {
            AntGraph::Path* current_path = ant.nextIteration(*this); // TODO: посмотреть правиьно ли его ищет nextIteration
            double res = 0;

            if (current_path != nullptr)
                if (path == nullptr || current_path->getSummaryDistance() > path->getSummaryDistance())
                    path = current_path;
        }

        return path;
    }
};


#endif //OPTIMIZATION_ANTCOLONY_H
