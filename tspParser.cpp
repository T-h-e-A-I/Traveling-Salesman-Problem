#include "tspParser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Point> TSPParser::parseTSPFile(const std::string& filename)
{
    std::vector<Point> points;
    std::ifstream file(filename);
    std::string line;
    bool readingCoords = false;

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return points;
    }

    while (getline(file, line))
    {
        if (line.find("NODE_COORD_SECTION") != std::string::npos)
        {
            readingCoords = true;
            continue;
        }

        if (readingCoords && !line.empty() && line.find("EOF") == std::string::npos)
        {
            std::istringstream iss(line);
            int index;
            double x, y;

            if (iss >> index >> x >> y)
            {
                points.emplace_back(index - 1, x, y);
            }
        }
    }

    return points;
}
