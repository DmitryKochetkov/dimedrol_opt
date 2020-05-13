//
// Created by dimedrol on 26.04.2020.
//

#ifndef OPTIMIZATION_MATHFUNCTION_H
#define OPTIMIZATION_MATHFUNCTION_H

#include <vector>
#include <stdexcept>

class Point {
private:
    int dimension;
    std::vector<double> coord;

public:
    explicit Point(const std::vector<double> &coord) : coord(coord) {
        this->dimension = coord.size();
    }

    std::vector<double> getCoord() const {
        return coord;
    }

    double getCoord(size_t i) const {
        return coord.at(i);
    }

    int getDimension() const {
        return dimension;
    }

    void setCoord(const std::vector<double> &coord) {
        if (coord.size() != this->coord.size())
            throw std::runtime_error("Point::setCoord() - bad argument");
        this->coord = coord;
    }

    void setCoord(size_t variable_id, double value) {
        this->coord.at(variable_id) = value;
    }

    bool operator== (const Point& point) {
        if (point.getDimension() != this->getDimension())
            return false;
        for (int i = 0; i < point.getDimension(); i++)
            if (this->getCoord(i) != point.getCoord(i))
                return false;
        return true;
    }

    Point operator+ (const Point& point) {
        if (point.getDimension() != this->getDimension())
            throw std::runtime_error("Point::operator+ - bad argument");

        std::vector<double> sumCoord(point.getDimension());
        for (int i = 0; i < point.getDimension(); i++) {
            sumCoord[i] = this->getCoord(i) + point.getCoord(i);
        }
        return Point(sumCoord);
    }

    Point operator- (const Point& point) {
        if (point.getDimension() != this->getDimension())
            throw std::runtime_error("Point::operator+ - bad argument");

        std::vector<double> sumCoord(point.getDimension());
        for (int i = 0; i < point.getDimension(); i++) {
            sumCoord[i] = this->getCoord(i) - point.getCoord(i);
        }
        return Point(sumCoord);
    }

    Point operator* (double number) { //TODO: сделать двусторонним, возможно путем вынесения вне класса
        std::vector<double> resultCoord(this->getCoord());
        for (int i = 0; i < this->getDimension(); i++)
            resultCoord[i] = getCoord(i) * number;
        return Point(resultCoord);
    }

};

class MathFunction {
private:
    int dimension;
public:
    explicit MathFunction(size_t dimension);

    virtual int getDimension() const;

    virtual double getValue(std::vector<double> x) = 0;
    virtual double getDerivative(std::vector<double> x) = 0; //TODO: is it necessary?

    virtual double getValue(const Point& point) {
        return this->getValue(point.getCoord());
    };
    virtual double getDerivative(Point point) {
        return this->getDerivative(point.getCoord());
    }; //TODO: is it necessary?

    virtual std::vector<double> getGlobalMinimumPoint() = 0;
    virtual double getGlobalMinimum() = 0;
};

class SphereFunction: public MathFunction {
public:
    explicit SphereFunction(size_t dimension);

private:

    double getValue(std::vector<double> x) override;

    double getDerivative(std::vector<double> x) override;

public:
    std::vector<double> getGlobalMinimumPoint() override;

    double getGlobalMinimum() override;
};

class RastriginFunction: public MathFunction {
public:
    explicit RastriginFunction(size_t dimension);

    double getValue(std::vector<double> x) override;

    double getDerivative(std::vector<double> x) override;

    std::vector<double> getGlobalMinimumPoint() override;

    double getGlobalMinimum() override;
};

class SchwefelFunction: public MathFunction {
public:
    explicit SchwefelFunction(size_t dimension);

public:
    double getValue(std::vector<double> x) override;

    double getDerivative(std::vector<double> x) override;

    std::vector<double> getGlobalMinimumPoint() override;

    double getGlobalMinimum() override;
};

#endif //OPTIMIZATION_MATHFUNCTION_H
