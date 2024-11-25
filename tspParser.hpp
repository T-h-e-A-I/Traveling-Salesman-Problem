#ifndef TSP_PARSER_HPP
#define TSP_PARSER_HPP

#include <vector>
#include <string>
#include "point.hpp"

class TSPParser {
public:
    static std::vector<Point> parseTSPFile(const std::string& filename);
};

#endif // TSP_PARSER_HPP
