//
// Created by dimedrol on 11.05.2020.
//

#include <algorithm>
#include "BeeColony.h"
#include "QuickRandom.h"

BeeColony::BeeColony(std::shared_ptr<MathFunction> function, int size, double variableLowerBounds, double variableUpperBounds) {
    this->function = function;

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
    for (auto foodSource: foodSources)
        employees.push_back(new Bee(foodSource));

    //инициализация наблюдателей TODO: сделать координаты не случайными, а выбирать пчелу??
    for (int i = 0; i < size/2; i++) {
        //create an employer bee in random coordinates
        std::vector<double> rand_coord;
        for (int j = 0; j < function->getDimension(); j++)
            rand_coord.push_back(get_random(variableLowerBounds, variableUpperBounds));
        onlookers.push_back(new Bee(Point(rand_coord)));
    }

    //evaluate and save fitness of each food source positions TODO: implement in bee::setCoord
}

std::vector<Point> BeeColony::findOptimal(int iterations) {
    for (int it = 0; it < iterations; it++) {
        //фаза рабочих пчел
        for (int i = 0; i < employees.size(); i++) {
            //выбор случайного партнера для сравнения
            int partner_id = i;
            while (partner_id == i)
                partner_id = get_random(0, employees.size() - 1);

            //выбор случайной переменной для изменения
            int variable_id = get_random(0, function->getDimension() - 1);

            Point newPosition = employees[i]->getPosition();
            newPosition.setCoord(variable_id,
                    employees[i]->getPosition().getCoord(variable_id) +
                    (employees[partner_id]->getPosition().getCoord(variable_id) - employees[i]->getPosition().getCoord(variable_id)) * get_random(-1.0, 1.0));
            //Point newPosition = employees[i]->getPosition() + (employees[partner_id]->getPosition() - employees[i]->getPosition()) * get_random(-1.0, 1.0);
            if (getFitness(newPosition) > getFitness(employees[i]->getPosition()))
                employees[i]->setPosition(Point(newPosition));
        }

        double fitnessSum = 0.0;
        for (auto bee: employees)
            fitnessSum += getFitness(bee->getPosition());

        auto employees_to_onlook = employees;

        //расчет вероятностей выбора рабочих пчел
        std::vector<double> probabilities(employees.size());
        for (int i = 0; i < employees.size(); i++)
            probabilities[i] = getFitness(employees[i]->getPosition()) / fitnessSum;

        //сортировка по вероятностям
        std::vector<size_t> permutation(employees_to_onlook.size());
        std::iota(permutation.begin(), permutation.end(), 0);
        std::sort(permutation.begin(), permutation.end(), [&](size_t i, size_t j) {return probabilities[i] < probabilities[j];});
        std::transform(permutation.begin(), permutation.end(), employees_to_onlook.begin(), [&](std::size_t i) { return employees_to_onlook[i];});

//        //наблюдатели выбирают рабочих
//        for (auto bee: onlookers) {
//            double choice = get_random(0.0, 1.0);
//            for (int i = 0; i < probabilities.size(); i++)
//                if (choice > probabilities[i]) {
//                    //choose employees_to_onlook[i]
//                    break;
//                }
//            //наблюдатели выбирают одну переменную в одном источнике пищи и меняют ее
//            double newValue =
//            onlookers.getFoodSource().setVariable(id, value);
//        }


//        //запоминаем лучшее решение (только среди рабочих?) (и что значит лучшее?)
//        for (auto bee: employees)
//            if (getFitness())
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

Point BeeColony::Bee::getPosition() const {
    return position;
}

void BeeColony::Bee::setPosition(const Point &position) {
    this->position = position;
}

BeeColony::Bee::Bee(Point point): position(point) {
}
