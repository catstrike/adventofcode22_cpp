#ifndef __DAY_06_SHARED_H__
#define __DAY_06_SHARED_H__

#include <stdexcept>
#include <unordered_map>

#define NOT_FOUND -1

template <class ItemType>
class Bag
{
    std::unordered_map<ItemType, int> counters;
    int balance {0};

public:
    bool is_balanced()
    {
        return balance == 0;
    }

    bool add(ItemType item)
    {
        auto count = counters[item];

        if (count >= 1) {
            balance += 1;
        }

        counters[item] += 1;

        return balance == 0;
    }

    bool remove(ItemType item)
    {
        auto count = counters[item];

        if (count == 0) {
            throw new std::invalid_argument("Can't remove the item that doesn't exist in the bag");
        }

        if (count > 1) {
            balance -= 1;
        }
        
        counters[item] -= 1;

        return balance == 0;
    }
};

int find_begin_of_packet(const std::string& line, int window_size)
{
    Bag<std::string::value_type> bag;

    // Init window
    int front = 0;
    int back = 0;

    for (; front < line.size() && front < window_size; front += 1) {
        bag.add(line[front]);
    }

    if (front < window_size) {
        throw new std::invalid_argument("The size of message should be at least 4 symbols!");
    }

    for (; front < line.size() && !bag.is_balanced(); front += 1, back += 1) {
        bag.add(line[front]);
        bag.remove(line[back]);
    }

    return front < line.size() ? front : NOT_FOUND;
}

#endif // __DAY_05_SHARED_H__