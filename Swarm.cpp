//
// Created by dimedrol on 28.04.2020.
//

#include <random>
#include "Swarm.h"

//случайное число из диапазона
inline double get_random(double min_range, double max_range) {
    std::random_device r;
    std::uniform_real_distribution<double> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}

Swarm::Swarm(
        std::shared_ptr<MathFunction> objective, size_t size,
        double lo_bounds, double up_bounds,
        double currentVelocityRatio, double localVelocityRatio, double globalVelocityRatio
        ) {
    this->objective = objective;
    this->currentVelocityRatio = currentVelocityRatio;
    this->localVelocityRatio = localVelocityRatio;
    this->globalVelocityRatio = globalVelocityRatio;

    for (int i = 0; i < size; i++)
        particles.push_back(Particle(*this, objective->getDimension(), lo_bounds, up_bounds));

    globalBestCoord = particles[0].getCoord();
    globalBestMinimum = objective->getValue(particles[0].getCoord());

    for (int i = 1; i < particles.size(); i++)
        if (objective->getValue(particles[0].getCoord()) < globalBestMinimum) {
            globalBestCoord = particles[i].getCoord();
            globalBestMinimum = objective->getValue(particles[0].getCoord());
        }
}

const std::vector<double> &Swarm::getGlobalBestCoord() const {
    return globalBestCoord;
}

double Swarm::getGlobalBestMinimum() const {
    return globalBestMinimum;
}

void Swarm::nextIteration() {
    for (Particle particle: particles) {
        particle.nextIteration(*this);
    }

    for (Particle particle: particles) {
        if (objective->getValue(particle.getCoord()) < globalBestMinimum)
        {
            globalBestCoord = particle.getCoord();
            globalBestMinimum = objective->getValue(particle.getCoord());
        }
    }
}

Swarm::Particle::Particle(Swarm& parent, size_t dimension, double lo_bounds, double up_bounds) {
    coord.resize(dimension);
    velocity.resize(dimension);
    for (int i = 0; i < dimension; i++) {
        coord[i] = get_random(lo_bounds, up_bounds);
        velocity[i] = get_random(lo_bounds, up_bounds);
    }
    bestCoord = std::vector<double>(coord);
    bestMinimum = parent.objective->getValue(coord);
}

const std::vector<double> &Swarm::Particle::getCoord() const {
    return coord;
}

void Swarm::Particle::nextIteration(Swarm& swarm) {

    std::vector<double> rndCurrent(coord.size()); // Случайный вектор для коррекции скорости с учетом лучшей позиции данной частицы
    std::vector<double> rndGlobal(coord.size()); //Случайный вектор для коррекции скорости с учетом лучшей глобальной позиции всех частиц

    for (int i = 0; i < coord.size(); i++)
    {
        rndCurrent[i] = get_random(0.0, 1.0);
        rndGlobal[i] = get_random(0.0, 1.0);
    }

    double velocityRatio = swarm.localVelocityRatio + swarm.globalVelocityRatio;
    double commonRatio = (2.0 * swarm.currentVelocityRatio /
                   (std::abs(2.0 - velocityRatio - sqrt(velocityRatio * velocityRatio - 4.0 * velocityRatio))));

    //Расчет новой скорости
    for (int i = 0; i < velocity.size(); i++) {
        velocity[i] *= commonRatio;

        velocity[i] += commonRatio * swarm.localVelocityRatio * rndCurrent[i] * (bestCoord[i] - coord[i]);

        velocity[i] += commonRatio * swarm.globalVelocityRatio * rndGlobal[i] * (swarm.getGlobalBestCoord()[i] - coord[i]);
    }

    //Обновение позиции частицы
    for (int i = 0; i < coord.size(); i++)
        coord[i] += velocity[i];

    //Расчет целевой функции
    double objValue = swarm.objective->getValue(coord);
    if (objValue < bestMinimum) {
        bestCoord = getCoord();
        bestMinimum = objValue;
    }
}
