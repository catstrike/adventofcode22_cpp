#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int> callories {0};

    auto it = std::begin(callories);

    for (std::string value; std::getline(std::cin, value);) {
        if (value.empty()) {
            callories.push_back(0);
            it = std::prev(std::end(callories));
            continue;
        }

        *it += std::stoi(value);
    }

    std::sort(
        std::begin(callories),
        std::end(callories),
        std::greater<int>()
    );

    int max = std::accumulate(
        std::begin(callories),
        std::begin(callories) + std::min((int)callories.size(), 3),
        0
    );

    std::cout << max << std::endl;

    return 0;
}