#ifndef CONSTRUCTIVE_HPP
#define CONSTRUCTIVE_HPP

#include <vector>

class ConstructiveHeuristics {
public:
    static std::vector<int> nearestNeighbor(const std::vector<std::vector<double>>& distances,
                                           int dimension,
                                           int startCity = -1);

    static std::vector<int> nearestInsertion(const std::vector<std::vector<double>>& distances,
                                            int dimension);

    static std::vector<int> farthestInsertion(const std::vector<std::vector<double>>& distances,
                                             int dimension);
};

#endif