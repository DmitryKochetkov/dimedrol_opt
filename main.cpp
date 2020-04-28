#include <iostream>
#include "MathFunction.h"
#include "Swarm.h"
#include "PointFormat.h"

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

}

void beeColonyOptimization() {

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
            antColonyOptimization();
            break;

        case 3:
            beeColonyOptimization();
            break;

        default:
            return 0;
    }

    return 0;
}
