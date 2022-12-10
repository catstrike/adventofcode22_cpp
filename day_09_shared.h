#ifndef __DAY_09_SHARED_H__
#define __DAY_09_SHARED_H__

#include <functional>
#include <stdexcept>
#include <charconv>

struct Vector2DInt
{
    int x;
    int y;

public: // - Lifecycle
    Vector2DInt()
        : x(0)
        , y(0)
    {}

    Vector2DInt(int x, int y)
        : x(x)
        , y(y)
    {}

public: // - Public
    Vector2DInt operator+ (const Vector2DInt& other) const
    {
        return Vector2DInt(x + other.x, y + other.y);
    }

    Vector2DInt operator- (const Vector2DInt& other) const
    {
        return Vector2DInt(x - other.x, y - other.y);
    }

    Vector2DInt& operator+= (const Vector2DInt& other) 
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    bool operator== (const Vector2DInt& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!= (const Vector2DInt& other) const
    {
        return !(*this == other);
    }
};

template<>
struct std::hash<Vector2DInt>
{
    std::size_t operator() (const Vector2DInt& vector) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(vector.x);
        std::size_t h2 = std::hash<int>{}(vector.y);
        return h1 ^ (h2 << 1);
    }
};

struct IWorld
{
    virtual void move_head(const Vector2DInt& direction) = 0;
    virtual int total_tail_positions() = 0;
};

void execute_line(const std::string& line, IWorld* world)
{
    if (line.size() < 3) {
        throw new std::invalid_argument("Bad input");
    }

    char command = line[0];
    int steps_count;
    
    if (std::from_chars(line.c_str() + 2, line.c_str() + line.size(), steps_count).ec != std::errc()) {
        throw new std::invalid_argument("Can't get the number of steps");
    }
    const Vector2DInt up(0, 1);
    const Vector2DInt down(0, -1);
    const Vector2DInt right(1, 0);
    const Vector2DInt left(-1, 0);

    Vector2DInt direction;

    switch (command) {
        case 'L': direction = left; break;
        case 'R': direction = right; break;
        case 'U': direction = up; break;
        case 'D': direction = down; break;
    }

    for (int i = 0; i < steps_count; ++i) {
        world->move_head(direction);
    }
}

#endif // __DAY_09_SHARED_H__
