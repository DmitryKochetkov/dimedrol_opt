//
// Created by dimedrol on 30.04.2020.
//

#ifndef OPTIMIZATION_QUICKRANDOM_H
#define OPTIMIZATION_QUICKRANDOM_H

#include <random>

//случайное число из диапазона
inline double get_random(double min_range, double max_range) {
    std::random_device r;
    std::uniform_real_distribution<double> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}

inline int get_random(int min_range, int max_range) {
    std::random_device r;
    std::uniform_int_distribution<int> unif(min_range, max_range);
    std::default_random_engine eng(r());
    return unif(eng);
}


#endif //OPTIMIZATION_QUICKRANDOM_H
