#include <iostream>
#include <string>

#include "day_06_shared.h"


int main()
{
    std::string line;
    
    if (!std::getline(std::cin, line)) {
        return 1;
    }

    auto result = find_begin_of_packet(line, 14);

    std::cout << result << std::endl;

    return 0;
}