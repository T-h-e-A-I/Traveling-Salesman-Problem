#ifndef TSP_SOLVER_HPP
#define TSP_SOLVER_HPP

#include <vector>
#include <map>
#include "point.hpp"

class TSPSolver {
private:
    std::vector<Point> cities;
    std::vector<std::vector<double>> distances;
    int dimension;

    double calculateDistance(const Point &p1, const Point &p2) const;
    void computeDistanceMatrix();

public:
    TSPSolver(const std::vector<Point> &points);
    double calculateTourLength(const std::vector<int> &tour) const;
    std::map<std::string, std::pair<std::vector<int>, double>> solveCombined();
};

#endif