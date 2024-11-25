#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "tspSolver.hpp"
#include "tspParser.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <tsp_file>" << endl;
        return 1;
    }

    vector<Point> points = TSPParser::parseTSPFile(argv[1]);

    if (points.empty())
    {
        cerr << "No valid points were read!" << endl;
        return 1;
    }

    TSPSolver solver(points);


    auto results = solver.solveCombined();


    cout << "\nResults for TSP instance:" << endl;
    cout << string(50, '-') << endl;

    double bestLength = numeric_limits<double>::infinity();
    string bestMethod;

    for (const auto &[method, result] : results)
    {
        cout << "\nMethod: " << method << endl;
        cout << "Tour length: " << fixed << setprecision(2) << result.second << endl;

        if (result.second < bestLength)
        {
            bestLength = result.second;
            bestMethod = method;
        }
    }

    cout << "\nBest Result:" << endl;
    cout << "Method: " << bestMethod << endl;
    cout << "Tour length: " << fixed << setprecision(2) << bestLength << endl;

    cout << "\nBest tour:" << endl;
    for (int city : results[bestMethod].first)
    {
        cout << city + 1 << " ";
    }
    cout << endl;

    return 0;
}