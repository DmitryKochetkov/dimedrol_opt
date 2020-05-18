//
// Created by dimedrol on 29.04.2020.
//

#include "AntColony.h"

AntGraph::Path* AntColony::Ant::nextIteration(AntColony &antColony) {
    visited = std::vector<Graph::Vertex*>();
    visited.push_back(start);
    double length = 0.0;

    //пока не обошли гамильтонов цикл
    while (visited.size() != antColony.graph.getVertices().size()) {

        //расчет знаменателя вероятности перехода - суммы параметров для каждого смежного ребра
        double denominator = 0.0;
        for (Graph::Vertex* vertex: antColony.graph.getAdjacent(getCurrentLocation())) {
            AntGraph::Edge* edge = antColony.graph.getEdge(getCurrentLocation()->getId(), vertex->getId());
            denominator += pow(edge->getPheromone(), antColony.pheromone_importance) +
                           1.0 / pow(edge->getWeight(), antColony.distance_importance);
        }
        if (denominator == 0.0)
            throw std::runtime_error("Ant::nextIteration - probability denominator is zero."); //TODO: fix nullptr; get adjacent returns null; bad architecture

        //сюда запоминаем вероятности перехода в каждую из смежных вершин
        std::vector<Graph::Vertex*> adjacent;
        std::vector<double> probabilities;

        for (Graph::Vertex* vertex: antColony.graph.getAdjacent(getCurrentLocation())) {
            if (std::find(visited.begin(), visited.end(), vertex) == visited.end()) { //если данну вершину еще не посетили
                AntGraph::Edge *edge = antColony.graph.getEdge(getCurrentLocation()->getId(), vertex->getId());

                double probability =
                        pow(edge->getPheromone(), antColony.pheromone_importance) +
                        1.0 / pow(edge->getWeight(), antColony.distance_importance);
                probability /= denominator;

                probabilities.push_back(probability);
                adjacent.push_back(vertex);
            }
        }

        //сортировка вершин и вероятностей перехода в них по вероятностям
        std::vector<size_t> permutation(adjacent.size());
        std::iota(permutation.begin(), permutation.end(), 0);
        std::sort(permutation.begin(), permutation.end(), [&](size_t i, size_t j) {return probabilities[i] < probabilities[j];});
        std::transform(permutation.begin(), permutation.end(), adjacent.begin(), [&](std::size_t i) { return adjacent[i];});

        // поиск первого значения, большего случайного нормально распределенного числа

        Graph::Vertex* next = nullptr;

        if (adjacent.empty()) //TODO: handle wrong path
            break;

        double choice = get_random(0.0, 1.0);
        for (int i = 0; i < probabilities.size(); i++) {
            if (probabilities[i] > choice)
                next = adjacent[i];
        }

        if (next == nullptr)
            next = adjacent.back();

        length += antColony.graph.getEdge(getCurrentLocation()->getId(), next->getId())->getWeight(); // запоминаем длину пройденного ребра
        visited.push_back(next); //переход в следующую вершину
    }

    if (std::unique(visited.begin(), visited.end()) != visited.end())
        std::cout << "Ant::nextIteration(): path contains duplicates" << std::endl;

//    if (std::find(
//            antColony.graph.getAdjacent(visited.back()).begin(),
//            antColony.graph.getAdjacent(visited.back()).end(),
//            visited.front()) != antColony.graph.getAdjacent(visited.back()).end())
//        visited.push_back(start);
//    else return nullptr;

    Graph::Path* path = new Graph::Path(&antColony.graph, start);
//    for (int i = 0; i < visited.size() - 1; i++) {
//        //собираем путь
//        path.addNextVertex(antColony.graph.getEdge(visited[i]->getId(), visited[i+1]->getId()));
//        //для всех ребер обновить феромоны после прохода муравья
//        antColony.graph.getEdge(visited.at(i)->getId(), visited.at(i+1)->getId())->setPheromone(antColony.pheromone_multiplier/length);
//    }

    for (int i = 1; i < visited.size() - 1; i++) {
        path->addNextVertex(visited[i]);
        antColony.graph.getEdge(visited.at(i)->getId(), visited.at(i+1)->getId())->setPheromone(antColony.pheromone_multiplier/length);
    }
    path->addNextVertex(visited.back());

    //испарение феромонов на всех ребрах
    antColony.graph.vaporize(antColony.pheromone_evaporation);

    if (path->isHamilton())
        return path;
    else return nullptr;

}
