#include <iostream>
#include <memory>

#include <string>
#include <unordered_set>
#include <array>

#include "day_09_shared.h"

class World : public IWorld
{
    static const int folowers_count = 9; 

    Vector2DInt my_head;
    std::array<Vector2DInt, folowers_count> my_knots {};

    std::unordered_set<Vector2DInt> tail_positoins;

public:
    World()
        : my_head(0, 0)
    {
        tail_positoins.insert(tail());
    }

    void move_head(const Vector2DInt& direction)
    {
        my_head += direction;

        Vector2DInt head = my_head;

        for (int i = 0; i < folowers_count; i++) {
            auto knot = my_knots[i];
            if (!is_far(head, knot)) {
                return;
            }

            knot += get_folowing_direction(head, knot);
            head = my_knots[i] = knot;
        }

        tail_positoins.insert(tail());
    }

    int total_tail_positions()
    {
        return tail_positoins.size();
    }

    const Vector2DInt& tail()
    {
        return my_knots[folowers_count - 1];
    }

private:
    static Vector2DInt get_folowing_direction(const Vector2DInt& head, const Vector2DInt& tail)
    {
        auto diff = head - tail;
        return Vector2DInt(normalize(diff.x), normalize(diff.y));
    }

    static int normalize(int n)
    {
        return n == 0 ? 0 : n < 0
            ? -1
            : 1;
    }

    static bool is_far(const Vector2DInt& first, const Vector2DInt& second)
    {
        auto distance = first - second;

        return std::abs(distance.x) > 1 || std::abs(distance.y) > 1;
    }
};

int main()
{
    World* world = new World();

    for (std::string line; std::getline(std::cin, line);) {
        execute_line(line, world);
    }

    std::cout << world->total_tail_positions() << std::endl;

    delete world;

    return 0;
}