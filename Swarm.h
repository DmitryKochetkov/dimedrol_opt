//
// Created by dimedrol on 28.04.2020.
//

#ifndef OPTIMIZATION_SWARM_H
#define OPTIMIZATION_SWARM_H


#include <bits/unique_ptr.h>
#include <memory>
#include "MathFunction.h"

//рой частиц
class Swarm {
    class Particle {
        std::vector<double> coord;
        std::vector<double> velocity;

        std::vector<double> bestCoord;
        double bestMinimum;

    public:
        Particle(Swarm& parent, size_t dimension, double lo_bounds, double up_bounds);

        const std::vector<double> &getCoord() const;

        void nextIteration(Swarm& swarm);

    };

    std::shared_ptr<MathFunction> objective;
    std::vector<Particle> particles;
    double currentVelocityRatio;
    double localVelocityRatio;
    double globalVelocityRatio;

    std::vector<double> globalBestCoord;
    double globalBestMinimum;

public:
    // objective - целевая функция
    // size - размер роя
    // lo_bounds - нижняя граница распределения
    // up_bounds - верхняя граница распределения
    // currentVelocityRatio - масштабирующий коэффициент скорости
    // localVelocityRatio - влияние локальной точки минимума на скорость
    // globalVelocityRatio - влияние глобальной точки минимума на скорость
    Swarm(
            std::shared_ptr<MathFunction> objective, size_t size,
            double lo_bounds, double up_bounds,
            double currentVelocityRatio, double localVelocityRatio, double globalVelocityRatio);
    void nextIteration();

    const std::vector<double> &getGlobalBestCoord() const;

    double getGlobalBestMinimum() const;
};


#endif //OPTIMIZATION_SWARM_H
