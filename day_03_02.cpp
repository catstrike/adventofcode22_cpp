#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <stdexcept>

const int GROUP_SIZE = 3;

template <class Item, class It>
std::unordered_set<Item> get_intersection(const std::unordered_set<Item> &first, It second_begin, It second_end)
{
    std::unordered_set<Item> result;

    for (It it = second_begin; it != second_end; std::advance(it, 1)) {
        if (first.find(*it) == std::end(first)) {
            continue;
        }

        result.insert(*it);
    }

    return result;
} 

constexpr
int get_priority(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }

    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }

    throw new std::invalid_argument(std::string("Unexpected item code ") + c);
}

int main()
{
    int result {0};

    for (std::string line; std::getline(std::cin, line);) {
        std::unordered_set<char> group_items(
            std::begin(line),
            std::end(line)
        );

        for (int i = 0; i < GROUP_SIZE - 1; i += 1) {
            if (!std::getline(std::cin, line)){
                throw new std::invalid_argument("Group should have at least 3 Elfs");
            }

            group_items = get_intersection(
                group_items,
                std::begin(line),
                std::end(line)
            );
        }

        if (group_items.size() != 1) {
            throw new std::invalid_argument("Rucksacks in the group should have exactly one item in common!");
        }

        result += get_priority(*std::begin(group_items));
    }

    std::cout << result << std::endl;

    return 0;
}