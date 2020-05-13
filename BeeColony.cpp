//
// Created by dimedrol on 11.05.2020.
//

#include <algorithm>
#include <iostream>
#include "BeeColony.h"
#include "QuickRandom.h"

BeeColony::BeeColony(std::shared_ptr<MathFunction> function, int size, double variableLowerBounds, double variableUpperBounds) {
    this->function = function;
    this->variableLowerBounds = variableLowerBounds;
    this->variableUpperBounds = variableUpperBounds;

    //термины:
    //solution - значение функции в источнике пищи
    //fitness - см. getFitness(point)
    //trial vector - если источник пищи дает новое решение, то trial[i]++; - это все рабочие

    //инциализация источников пищи в случайных координатах
    for (int i = 0; i < size/2; i++) {
        //создает рабочих пчел в случайных координатах
        std::vector<double> rand_coord;
        for (int j = 0; j < function->getDimension(); j++)
            rand_coord.push_back(get_random(variableLowerBounds, variableUpperBounds));
        foodSources.push_back(Point(rand_coord));
    }

    //инициализация рабочих пчел в источниках пищи
    for (auto& foodSource: foodSources) {
        employees.push_back(new Bee(&foodSource));
        onlookers.push_back(new Bee(nullptr));
    }
}

std::vector<Point> BeeColony::findOptimal(int iterations) {
    std::vector<size_t> trial(foodSources.size());

    //TODO: везде менять координаты фуд сорса, а в пчелах хранить указатели на них
    for (int it = 0; it < iterations; it++) {
        //фаза рабочих пчел
        for (int i = 0; i < employees.size(); i++) {
            //выбор случайного партнера для сравнения
            int partner_id = i;
            while (partner_id == i)
                partner_id = get_random(0, employees.size() - 1);

            //выбор случайной переменной для изменения
            int variable_id = get_random(0, function->getDimension() - 1);

            Point newPosition = *employees[i]->getPosition();
            newPosition.setCoord(variable_id,
                    employees[i]->getPosition()->getCoord(variable_id) +
                    (employees[partner_id]->getPosition()->getCoord(variable_id) - employees[i]->getPosition()->getCoord(variable_id)) * get_random(-1.0, 1.0));
            //Point newPosition = employees[i]->getPosition() + (employees[partner_id]->getPosition() - employees[i]->getPosition()) * get_random(-1.0, 1.0);

            if (newPosition.getCoord(variable_id) < variableLowerBounds)
                newPosition.setCoord(variable_id, variableLowerBounds);
            else if (newPosition.getCoord(variable_id) > variableUpperBounds)
                newPosition.setCoord(variable_id, variableUpperBounds);

            if (getFitness(newPosition) > getFitness(*employees[i]->getPosition())) {
                employees[i]->setPosition(newPosition);
                trial[i] = 0;
            }
            else trial[i]++;
        }

        //фаза наблюдателей
        double fitnessSum = 0.0;
        for (auto bee: employees)
            fitnessSum += getFitness(*bee->getPosition());

        //расчет вероятностей выбора рабочих пчел TODO: а должна быть вероятность выбора ФУД СОРСА, и там без всякой сортировки
        std::vector<double> probabilities(employees.size());
        for (int i = 0; i < employees.size(); i++)
            probabilities[i] = getFitness(*employees[i]->getPosition()) / fitnessSum;

        //наблюдатели выбирают рабочих
        for (int i = 0; i < onlookers.size(); i++) {
            double choice = get_random(0.0, 1.0);

            if (choice < probabilities[i]) {
                onlookers[i]->setPosition(employees[i]->getPosition());

                //наблюдатели выбирают одну переменную в одном источнике пищи и меняют ее
                size_t variable_id = get_random(0, function->getDimension() - 1);
                size_t partner_id = get_random(0, foodSources.size() - 1);

                //TODO: устранить дублирование кода с newPosition
                Point newPosition = *onlookers[i]->getPosition();
                newPosition.setCoord(variable_id,
                                     onlookers[i]->getPosition()->getCoord(variable_id) +
                                     (employees[partner_id]->getPosition()->getCoord(variable_id) -
                                      onlookers[i]->getPosition()->getCoord(variable_id)) * get_random(-1.0, 1.0));
                //Point newPosition = employees[i]->getPosition() + (employees[partner_id]->getPosition() - employees[i]->getPosition()) * get_random(-1.0, 1.0);

                if (newPosition.getCoord(variable_id) < variableLowerBounds)
                    newPosition.setCoord(variable_id, variableLowerBounds);
                else if (newPosition.getCoord(variable_id) > variableUpperBounds)
                    newPosition.setCoord(variable_id, variableUpperBounds);

                if (getFitness(newPosition) > getFitness(*employees[i]->getPosition())) {
                    onlookers[i]->setPosition(Point(newPosition));
                    trial[i] = 0;
                } else trial[i]++;

                onlookers[i]->setPosition(nullptr);
            }
            else {
                trial[i] = 0; //TODO: так?
            }
        }

        //фаза разведчиков

    }

    return foodSources;
}

BeeColony::~BeeColony() {
    for (auto bee: employees)
        delete bee;
}

double BeeColony::getFitness(const Point& point) const {
    if (function->getValue(point) >= 0)
        return 1/(1 + function->getValue(point));
    else return 1 + std::abs(function->getValue(point));
}

Point* BeeColony::Bee::getPosition() const {
    return position;
}

BeeColony::Bee::Bee(Point* point): position(point) {
}

void BeeColony::Bee::setPosition(Point* point) {
    Bee::position = point;
}

void BeeColony::Bee::setPosition(const Point & point) {
    if (point.getDimension() != this->position->getDimension()) {
        std::cout << "Bee::setPosition - Некорректная размерность, координаты отброшены" << std::endl;
        return;
    }
    position->setCoord(point.getCoord());
}
