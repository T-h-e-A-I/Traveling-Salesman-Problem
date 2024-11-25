#include "tspSolver.hpp"
#include "perturbativeHeuristics.hpp"
#include "constructiveHeuristics.hpp"
#include <cmath>

double TSPSolver::calculateDistance(const Point &p1, const Point &p2) const {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return round(sqrt(dx * dx + dy * dy));
}

void TSPSolver::computeDistanceMatrix() {
    distances.resize(dimension, std::vector<double>(dimension));
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            distances[i][j] = calculateDistance(cities[i], cities[j]);
        }
    }
}

TSPSolver::TSPSolver(const std::vector<Point> &points) : cities(points) {
    dimension = cities.size();
    computeDistanceMatrix();
}

double TSPSolver::calculateTourLength(const std::vector<int> &tour) const {
    double length = 0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        length += distances[tour[i]][tour[i + 1]];
    }
    length += distances[tour.back()][tour[0]]; 
    return length;
}

std::map<std::string, std::pair<std::vector<int>, double>> TSPSolver::solveCombined() {
    std::map<std::string, std::pair<std::vector<int>, double>> results;


    auto nnTour = ConstructiveHeuristics::nearestNeighbor(distances, dimension);
    auto niTour = ConstructiveHeuristics::nearestInsertion(distances, dimension);
    auto fiTour = ConstructiveHeuristics::farthestInsertion(distances, dimension);


    results["nearest_neighbor"] = {nnTour, calculateTourLength(nnTour)};
    results["nearest_insertion"] = {niTour, calculateTourLength(niTour)};
    results["farthest_insertion"] = {fiTour, calculateTourLength(fiTour)};

    std::vector<std::pair<std::vector<int>, std::string>> initialTours = {
        {nnTour, "nearest_neighbor"},
        {niTour, "nearest_insertion"},
        {fiTour, "farthest_insertion"}
    };

    for (const auto &[tour, name] : initialTours)
    {

        auto improvedTour = PerturbativeHeuristics::twoOpt(distances, tour);
        results[name + "_2opt"] = {improvedTour, calculateTourLength(improvedTour)};

        improvedTour = PerturbativeHeuristics::nodeSwap(distances, tour);
        results[name + "_nodeswap"] = {improvedTour, calculateTourLength(improvedTour)};

        improvedTour = PerturbativeHeuristics::nodeShift(distances, tour);
        results[name + "_nodeshift"] = {improvedTour, calculateTourLength(improvedTour)};
    }

    return results;
}
