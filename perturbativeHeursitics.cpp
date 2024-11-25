#include "perturbativeHeuristics.hpp"
#include <algorithm>

double PerturbativeHeuristics::calculateTourLength(const std::vector<std::vector<double> > &distances,
                                                   const std::vector<int> &tour)
{
    double length = 0;
    for (size_t i = 0; i < tour.size() - 1; i++)
    {
        length += distances[tour[i]][tour[i + 1]];
    }
    length += distances[tour.back()][tour[0]]; // Return to start
    return length;
}

std::vector<int> PerturbativeHeuristics::twoOpt(const std::vector<std::vector<double> > &distances,
                                                std::vector<int> tour,
                                                int maxIterations)
{
    bool improved = true;
    int iteration = 0;

    while (improved && iteration < maxIterations)
    {
        improved = false;
        iteration++;

        for (size_t i = 1; i < tour.size() - 2; i++)
        {
            for (size_t j = i + 1; j < tour.size(); j++)
            {
                if (j - i == 1)
                    continue;

                std::vector<int> newTour = tour;
                reverse(newTour.begin() + i, newTour.begin() + j + 1);

                if (calculateTourLength(distances, newTour) < calculateTourLength(distances, tour))
                {
                    tour = newTour;
                    improved = true;
                    break;
                }
            }
            if (improved)
                break;
        }
    }
    return tour;
}


std::vector<int> PerturbativeHeuristics::nodeSwap(const std::vector<std::vector<double> > &distances,
                                                 std::vector<int> tour,
                                                 int maxIterations)
{
    bool improved = true;
    int iteration = 0;

    while (improved && iteration < maxIterations)
    {
        improved = false;
        iteration++;

        for (size_t i = 1; i < tour.size() - 1; i++)
        {
            for (size_t j = i + 1; j < tour.size(); j++)
            {
                std::vector<int> newTour = tour;
                std::swap(newTour[i], newTour[j]);

                if (calculateTourLength(distances, newTour) < calculateTourLength(distances, tour))
                {
                    tour = newTour;
                    improved = true;
                    break;
                }
            }
            if (improved)
                break;
        }
    }

    return tour;
}


std::vector<int> PerturbativeHeuristics::nodeShift(const std::vector<std::vector<double> > &distances,
                                                   std::vector<int> tour,
                                                   int maxIterations)
{
    bool improved = true;
    int iteration = 0;

    while (improved && iteration < maxIterations)
    {
        improved = false;
        iteration++;

        for (size_t i = 1; i < tour.size() - 1; i++)
        {
            for (size_t j = 0; j < tour.size(); j++)
            {
                if (i == j || i == j - 1)
                    continue;

                std::vector<int> newTour = tour;
                int city = newTour[i];
                newTour.erase(newTour.begin() + i);
                newTour.insert(newTour.begin() + j, city);

                if (calculateTourLength(distances, newTour) < calculateTourLength(distances,tour))
                {
                    tour = newTour;
                    improved = true;
                    break;
                }
            }
            if (improved)
                break;
        }
    }

    return tour;
}
