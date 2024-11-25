#ifndef PERTURBATIVE_HPP
#define PERTURBATIVE_HPP

#include <vector>

class PerturbativeHeuristics
{
public:
    static std::vector<int> twoOpt(const std::vector<std::vector<double>> &distances,
                                   std::vector<int> tour,
                                   int maxIterations = 1000);

    static std::vector<int> nodeSwap(const std::vector<std::vector<double>> &distances,
                                     std::vector<int> tour,
                                     int maxIterations = 1000);

    static std::vector<int> nodeShift(const std::vector<std::vector<double>> &distances,
                                      std::vector<int> tour,
                                      int maxIterations = 1000);

private:
    static double calculateTourLength(const std::vector<std::vector<double>> &distances,
                                      const std::vector<int> &tour);
};

#endif