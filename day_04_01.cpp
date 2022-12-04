#include <iostream>
#include <string>

#include "day_04_shared.h"

int main()
{
    int result {0};

    for (std::string line; std::getline(std::cin, line);) {
        auto [first, second] = parse_line(line);
        
        if (first.contains_all(second) || second.contains_all(first)) {
            result += 1;
        }
    }

    std::cout << result << std::endl;

    return 0;
}