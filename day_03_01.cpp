#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <stdexcept>

using string_const_it = std::string::const_iterator;

std::tuple<string_const_it, string_const_it, string_const_it> get_compartments(const std::string& line)
{
    auto middle = std::cbegin(line);
    std::advance(middle, line.size() / 2);

    return std::make_tuple(
        std::cbegin(line),
        middle,
        std::cend(line)
    );
}

char get_common_item(string_const_it first, string_const_it second, string_const_it end)
{
    std::unordered_set<char> set;
    set.insert(first, second);

    for (auto it = second; it != end; std::advance(it, 1)) {
        if (set.find(*it) != std::end(set)) {
            return *it;
        }
    }

    throw new std::invalid_argument("Unexpected input!");
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
        auto [first, second, end] = get_compartments(line);
        char common = get_common_item(first, second, end);

        result += get_priority(common);
    }

    std::cout << result << std::endl;

    return 0;
}