#include <iostream>

#include <iterator>
#include <vector>

#include "day_08_shared.h"

class Range {
    int my_from;
    int my_to;

public:
    class iterator: public std::iterator<std::input_iterator_tag, int>{
        int my_value;
        int my_increment;

    public:
        explicit iterator(int value, int increment)
            : my_value(value)
            , my_increment(increment)
        {}

        iterator& operator++() { my_value += my_increment; return *this; }
        iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return my_value == other.my_value; }
        bool operator!=(iterator other) const { return !(*this == other); }
        value_type operator*() const { return my_value; }
    };

public:
    Range(int from, int to)
        : my_from(from)
        , my_to(to)
    {}

    int size() const { return std::abs(my_to - my_from); }

    iterator begin() const { return iterator(my_from, my_from < my_to ? 1 : -1); }
    iterator end() const { return iterator(my_to, my_from < my_to ? 1 : -1); }
};

int check_tree(int tree_height, int& max_tree_height, bool& mask)
{
    if (tree_height <= max_tree_height) {
        return 0;
    }

    max_tree_height = tree_height;

    if (mask) {
        return 0;
    }

    mask = true;

    return 1;
}

int scan_map(const ForestMap& map, ForestMask& mask, const Range& vrange, const Range& hrange)
{
    int result {};
    std::vector<int> vheights(vrange.size(), -1);

    for (auto i : hrange) {
        int hheight = -1;

        for (auto j : vrange) {
            bool tree_mask = mask[i][j];

            result += check_tree(map[i][j], hheight, tree_mask);
            result += check_tree(map[i][j], vheights[j], tree_mask);

            mask[i][j] = tree_mask;
        }
    }

    return result;
}

int count_visible_trees(const ForestMap& map)
{
    int height = map.size();
    int width = map[0].size();

    int result {};

    ForestMask mask(height, std::vector<bool>(width, false));

    result += scan_map(map, mask, Range(0, height), Range(0, width));
    result += scan_map(map, mask, Range(height - 1, -1), Range(width - 1, -1));

    return result;
}


int main()
{
    auto map = read_map(std::cin);
    auto result = count_visible_trees(map);

    std::cout << result << std::endl;
}