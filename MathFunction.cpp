//
// Created by dimedrol on 26.04.2020.
//

#include "MathFunction.h"
#include <cmath>

double SphereFunction::getValue(std::vector<double> x) {
    double result = 0.0;
    for (double var: x)
        result += var * var;
    return result;
}

double SphereFunction::getDerivative(std::vector<double> x) {
    return 0;
}

SphereFunction::SphereFunction(size_t dimension) : MathFunction(dimension) {}

std::vector<double> SphereFunction::getGlobalMinimumPoint() {
    return std::vector<double>(getDimension(), 0);
}

double SphereFunction::getGlobalMinimum() {
    return 0;
}

double RastriginFunction::getValue(std::vector<double> x) {
    double dimension = x.size();
    double result = dimension * 10; //TODO: параметры, вроде этой десятки, надо вынести в параметр метода или конструктора функции
    for (double var: x)
        result += var * var - 10 * cos(2 * M_PI * var);
    return result;
}

double RastriginFunction::getDerivative(std::vector<double> x) {
    return 0;
}

RastriginFunction::RastriginFunction(size_t dimension) : MathFunction(dimension) {}

std::vector<double> RastriginFunction::getGlobalMinimumPoint() {
    return std::vector<double>(getDimension(), 0);
}

double RastriginFunction::getGlobalMinimum() {
    return 0;
}

double SchwefelFunction::getValue(std::vector<double> x) {
    double dimension = x.size();
    double result = dimension * 10; //TODO: параметры, вроде этой десятки, надо вынести в параметр метода или конструктора функции
    for (double var: x)
        result += -var * sin(sqrt(std::abs(var)));
    return result;
}

double SchwefelFunction::getDerivative(std::vector<double> x) {
    return 0;
}

SchwefelFunction::SchwefelFunction(size_t dimension) : MathFunction(dimension) {}

std::vector<double> SchwefelFunction::getGlobalMinimumPoint() {
    return std::vector<double>(getDimension(), 420.9687);
}

double SchwefelFunction::getGlobalMinimum() {
    return 0;
}

MathFunction::MathFunction(size_t dimension) : dimension(dimension) {}

int MathFunction::getDimension() const {
    return dimension;
}
