//
// Created by dimedrol on 11.05.2020.
//

#ifndef OPTIMIZATION_BEECOLONY_H
#define OPTIMIZATION_BEECOLONY_H


#include <vector>
#include "MathFunction.h"

class BeeColony {
public:
    BeeColony(int size, double variableLowerBounds, double variableUpperBounds);

    std::vector<double> findOptimal(MathFunction* function, int iterations);
};


#endif //OPTIMIZATION_BEECOLONY_H
