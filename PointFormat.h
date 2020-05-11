//
// Created by dimedrol on 28.04.2020.
//

#ifndef OPTIMIZATION_POINTFORMAT_H
#define OPTIMIZATION_POINTFORMAT_H

#include <vector>
#include <string>

std::string pointToString(const std::vector<double>& x) {
    std::string result = "(";
    for (int i = 0; i < x.size() - 1; i++)
        result += std::to_string(x[i]) + "; ";
    result += std::to_string(x.back()) + ")";
    return result;
}

void tryReadDouble(double& out) {
    std::string input;
    std::getline(std::cin, input);

    //std::string::size_type sz;
    try {
        out = std::stod(input);
    }
    catch (std::invalid_argument& e) {
        return;
    }
}

#endif //OPTIMIZATION_POINTFORMAT_H
