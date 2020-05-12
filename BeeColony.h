//
// Created by dimedrol on 11.05.2020.
//

#ifndef OPTIMIZATION_BEECOLONY_H
#define OPTIMIZATION_BEECOLONY_H


#include <vector>
#include <memory>
#include "MathFunction.h"

class BeeColony {
    class Bee {
        Point position;

    public:
        Bee(Point point);

        Point getPosition() const;

        void setPosition(const Point &position);
    };

    std::vector<Bee*> employees; //рабочие пчелы
    std::vector<Bee*> onlookers; //пчелы-наблюдатели
    std::vector<Bee*> scouts; //пчелы-разведчики

    std::shared_ptr<MathFunction> function;
    std::vector<Point> foodSources;

    double getFitness(const Point &point) const;

public:
    BeeColony(std::shared_ptr<MathFunction> function, int size, double variableLowerBounds, double variableUpperBounds);

    virtual ~BeeColony();

    std::vector<Point> findOptimal(int iterations);
};


#endif //OPTIMIZATION_BEECOLONY_H
