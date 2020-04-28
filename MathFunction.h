//
// Created by dimedrol on 26.04.2020.
//

#ifndef OPTIMIZATION_MATHFUNCTION_H
#define OPTIMIZATION_MATHFUNCTION_H

#include <vector>

class MathFunction {
private:
    int dimension;
public:
    explicit MathFunction(size_t dimension);

    virtual int getDimension() const;

    virtual double getValue(std::vector<double> x) = 0;
    virtual double getDerivative(std::vector<double> x) = 0; //TODO: is it necessary?

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
