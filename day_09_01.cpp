#include <iostream>
#include <memory>

#include <string>
#include <unordered_set>

#include "day_09_shared.h"

class World : public IWorld
{
    Vector2DInt my_head;
    Vector2DInt my_tail;

    std::unordered_set<Vector2DInt> tail_positoins;

public:
    World()
        : my_head(0, 0)
        , my_tail(0, 0)
    {
        tail_positoins.insert(my_tail);
    }

    void move_head(const Vector2DInt& direction)
    {
        my_head += direction;

        if (!is_far(my_head, my_tail)) {
            return;
        }

        my_tail = my_head - direction;

        tail_positoins.insert(my_tail);
    }

    int total_tail_positions()
    {
        return tail_positoins.size();
    }

private:
    static bool is_far(const Vector2DInt& first, const Vector2DInt& second)
    {
        auto distance = first - second;

        return std::abs(distance.x) > 1 || std::abs(distance.y) > 1;
    }
};


int main()
{
    std::unique_ptr<World> world = std::make_unique<World>();

    for (std::string line; std::getline(std::cin, line);) {
        execute_line(line, world.get());
    }

    std::cout << world->total_tail_positions() << std::endl;

    return 0;
}