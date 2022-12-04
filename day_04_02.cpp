#include <iostream>
#include <tuple>
#include <array>
#include <stdexcept>
#include <string>

const std::string separators = "-,";

struct Range
{
    const int begin;
    const int end;

    Range(int begin, int end) 
        : begin(begin)
        , end(end) 
    {}

    int size() const
    {
        return end - begin;
    }

    bool contains_all(const Range& other) const
    {
        return other.begin >= begin && other.end <= end;
    }

    bool inside(int a) const
    {
        return a >= begin && a <= end;
    }

    bool overlaps(const Range& other) const
    {
        return inside(other.begin) || inside(other.end) ||
               other.inside(begin) || other.inside(end);
    }
};

constexpr
int to_int(const char c)
{
    if (c < '0' || c > '9') {
        throw new std::invalid_argument(std::string("Bad digit: ") + c);
    }

    return c - '0';
}

int to_int(const std::string& line, std::string::size_type begin, std::string::size_type end)
{
    int result = 0;

    for (int i = begin; i < end; i += 1) {
        result *= 10;
        result += to_int(line[i]);
    }

    return result;
}

Range parse_range(const std::string& line, std::string::size_type begin, std::string::size_type end)
{
    auto position = line.find('-', begin);

    if (position == std::string::npos || position >= end) {
        throw new std::invalid_argument("Bad range!");
    }

    return Range(
        to_int(line, begin, position),
        to_int(line, position + 1, end)
    );
}

std::tuple<Range, Range> parse_line(const std::string& line)
{
    std::array<int, 4> result;

    auto position = line.find(',');

    if (position == std::string::npos) {
        throw new std::invalid_argument("Bad input!");
    }

    return std::make_tuple(
        parse_range(line, 0, position),
        parse_range(line, position + 1, line.size())
    );
}

int main()
{
    int result {0};

    for (std::string line; std::getline(std::cin, line);) {
        auto [first, second] = parse_line(line);
        
        if (first.overlaps(second)) {
            result += 1;
        }
    }

    std::cout << result << std::endl;

    return 0;
}