#include <iostream>

#include <vector>

#include "day_08_shared.h"

struct Vector2DInt
{
    int i;
    int j;

    Vector2DInt(int i, int j)
        : i(i)
        , j(j)
    {}

    Vector2DInt operator+ (const Vector2DInt& other)
    {
        return Vector2DInt(i + other.i, j + other.j);
    }

    Vector2DInt& operator+= (const Vector2DInt& other)
    {
        i += other.i;
        j += other.j;

        return *this;
    }
};

bool on_map(const ForestMap& map, const Vector2DInt& position)
{
    int height = map.size();
    int width = map[0].size();

    return position.i >= 0 && position.i < height &&
           position.j >= 0 && position.j < width;
}

int ray_cast(const ForestMap& map, Vector2DInt start, Vector2DInt direction)
{
    int result {};
    int start_height = map[start.i][start.j];

    for (auto position = start + direction; on_map(map, position); position += direction) {
        int tree_height = map[position.i][position.j];

        result += 1;

        if (tree_height >= start_height) break;
    }

    return result;
}

int find_best_score(const ForestMap& map)
{
    int height = map.size();
    int width = map[0].size();

    const Vector2DInt up(-1, 0);
    const Vector2DInt down(1, 0);
    const Vector2DInt left(0, -1);
    const Vector2DInt right(0, 1);

    int result {};

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Vector2DInt position(i, j);

            int score = ray_cast(map, position, up) *
                ray_cast(map, position, down) *
                ray_cast(map, position, left) *
                ray_cast(map, position, right);

            if (score > result) {
                result = score;
            }
        }
    }

    return result;
}

int main()
{
    auto map = read_map(std::cin);
    auto result = find_best_score(map);

    std::cout << result << std::endl;
}