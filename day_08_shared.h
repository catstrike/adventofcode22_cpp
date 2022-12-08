#ifndef __DAY_08_SHARED_H__
#define __DAY_08_SHARED_H__

#include <stdexcept>

#include <vector>

using ForestMap = std::vector<std::vector<int>>;
using ForestMask = std::vector<std::vector<bool>>;

std::vector<int> parse_line(const std::string& line)
{
    std::vector<int> result;

    for (auto& c : line) {
        result.push_back(c - '0');
    }

    return result;
}

ForestMap read_map(std::basic_istream<char>& input)
{
    ForestMap map;

    int width = -1;

    for (std::string line; std::getline(input, line);) {
        if (width == -1) {
            width = line.size();
        } else if (width != line.size()) {
            throw new std::invalid_argument("The map should be rectangular");
        }
        
        map.push_back(parse_line(line));
    }

    return map;
}

#endif // __DAY_08_SHARED_H__