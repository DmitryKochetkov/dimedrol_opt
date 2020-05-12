#include <iostream>
#include "MathFunction.h"
#include "Swarm.h"
#include "PointFormat.h"
#include "Graph.h"
#include "AntColony.h"
#include "BeeColony.h"

void particleSwarmOptimization() {
    double optimalLowerBounds[3] = {-10.0, -5.12, -500.0};
    double optimalUpperBounds[3] = {10.0, 5.12, 500.0};

    std::cout << "Выберите размерность аргумента функции: ";
    int dimension;
    std::cin >> dimension;
    std::cout << "Выберите целевую функцию:" << std::endl;
    std::cout << "\t1. Функция сферы" << std::endl;
    std::cout << "\t2. Функция Растригина" << std::endl;
    std::cout << "\t3. Функция Швефеля" << std::endl;

    int foo_code;
    std::cin >> foo_code;

    std::shared_ptr<MathFunction> objective; //целевая функция

    switch (foo_code) {
        case 1:
            objective = std::shared_ptr<MathFunction>(new SphereFunction(dimension));
            break;

        case 2:
            objective = std::shared_ptr<MathFunction>(new RastriginFunction(dimension));
            break;

        case 3:
            objective = std::shared_ptr<MathFunction>(new SchwefelFunction(dimension));
            break;

        default:
            return;
    }

    std::cout << "Данная функция имеет минимум " << objective->getGlobalMinimum()
              << " в точке " << pointToString(objective->getGlobalMinimumPoint()) << std::endl;
    Swarm swarm(objective, 3000, optimalLowerBounds[foo_code - 1], optimalUpperBounds[foo_code - 1], 0.3, 2, 5);

    std::cout << "Введите количество итераций: ";
    int iterations;
    std::cin >> iterations;

    for (int i = 0; i < iterations; i++)
        swarm.nextIteration();

    std::cout << "Найденный минимум: " << swarm.getGlobalBestMinimum()
              << " в точке " << pointToString(swarm.getGlobalBestCoord());
}

void antColonyOptimization() {
    AntGraph graph;
    graph.addVertex("1");
    graph.addVertex("2");
    graph.addVertex("3");
    graph.addVertex("4");
    graph.addVertex("5");
    graph.addVertex("6");
    graph.addEdge("1", "2", 7);
    graph.addEdge("1", "3", 9);
    graph.addEdge("2", "3", 10);
    graph.addEdge("1", "6", 14);
    graph.addEdge("3", "6", 2);
    graph.addEdge("3", "4", 11);
    graph.addEdge("6", "5", 9);
    graph.addEdge("5", "4", 6);
    graph.addEdge("2", "4", 15);

    std::cout << "Введите размер колонии: ";
    int size;
    std::cin >> size;

    double distance_importance = 0.5;
    double pheromone_importance = 1.0;
    double pheromone_multiplier = 1.0;
    double pheromone_evaporation = 0.5;

    std::cout << "Введите коэффициент важности расстояния [по умолчанию " << distance_importance << "]: ";
    tryReadDouble(distance_importance);
    std::cout << "Введите коэффициент важности феромона [по умолчанию " << pheromone_importance << "]: ";
    tryReadDouble(pheromone_importance);
    std::cout << "Введите коэффициент к обратной пропорциональности в обновлении феромона [по умолчанию " << pheromone_multiplier << "]: ";
    tryReadDouble(pheromone_multiplier);
    std::cout << "Введите коэффициент испарения феромона [по умолчанию " << pheromone_evaporation << "]: ";
    tryReadDouble(pheromone_evaporation);

    AntColony antColony(graph, size, 0.5, 1.0, 1.0, 0.5); //todo: подобрать параметры

    std::cout << "Введите количество итераций: ";
    int iterations;
    std::cin >> iterations;

    //std::cout << "Оптимальный путь по какому-то еще алгоритму: " << std::endl;
    //и тут еще какая-то функция, которой нет

    std::cout << "Оптимальный путь по муравьиному алгоритму: " << std::endl;
    AntGraph::Path optimalPath = antColony.findOptimalPath(iterations);
    std::cout << optimalPath.to_string() << std::endl;
}

void antColonyTest() {
    AntGraph graph;
    graph.addVertex("1");
    graph.addVertex("2");
    graph.addVertex("3");
    graph.addVertex("4");
    graph.addVertex("5");
    graph.addVertex("6");
    graph.addEdge("1", "2", 7);
    graph.addEdge("1", "3", 9);
    graph.addEdge("2", "3", 10);
    graph.addEdge("1", "6", 14);
    graph.addEdge("3", "6", 2);
    graph.addEdge("3", "4", 11);
    graph.addEdge("6", "5", 9);
    graph.addEdge("5", "4", 6);
    graph.addEdge("2", "4", 15);

    int size = 100;

    double distance_importance = 0.5;
    double pheromone_importance = 1.0;
    double pheromone_multiplier = 1.0;
    double pheromone_evaporation = 0.5;

    int iterations = 100;
    AntColony antColony(graph, size, 0.5, 1.0, 1.0, 0.5); //todo: подобрать эвристики
    AntGraph::Path optimalPath = antColony.findOptimalPath(iterations); //ожидаем (3,5), (5,2), (2,1), (1,4), (4,6), (6,3) - длина 9


    std::cout << optimalPath.to_string() << std::endl;
}

void beeColonyOptimization() {
    int size = 100;
    std::shared_ptr<MathFunction> function(new SchwefelFunction(3));
    double variableLowerBounds = -500.0;
    double variableUpperBounds = 500.0;

    MathFunction* function = new SchwefelFunction(3);
    int iterations = 1000;

    std::vector<double> optimum = beeColony.findOptimal(function, iterations);
    std::cout << "Функция ? достигает максимума в точке " << pointToString(optimum) << std::endl;
}

void testPoint() {
    Point p1({0, 1, 2});
    Point p2({1, 3, -1});

    std::cout << pointToString((p1 * 2).getCoord()) << std::endl;
    std::cout << pointToString((p1 + p2).getCoord()) << std::endl;
    std::cout << pointToString((p1 - p2).getCoord()) << std::endl;
}

int main() {
    int algorithm;
    std::cout << "Выберите алгоритм: " << std::endl;
    std::cout << "\t1. Алгоритм роя частиц" << std::endl;
    std::cout << "\t2. Алгоритм муравьиной колонии" << std::endl;
    std::cout << "\t3. Алгоритм пчелиной колонии" << std::endl;

    std::cin >> algorithm;
    switch (algorithm) {
        case 1:
            particleSwarmOptimization();
            break;

        case 2:
            //antColonyOptimization();
            antColonyTest();
            break;

        case 3:
            beeColonyOptimization();
            break;

        case 4:
            testPoint();
            break;

        default:
            return 0;
    }

    return 0;
}
