#include <iostream>
#include <stdexcept>

#include <string>
#include <queue>

#include "day_10_shared.h"


class Machine : public MachineBase
{
    static const int line_size = 40;

    int my_position {1};

private:
    virtual void on_tick()
    {
        bool pixel_set = my_position >= my_state.x && my_position < (my_state.x + 3);
        char symbol = pixel_set ? '#' : '.';

        std::cout << symbol;

        my_position++;

        if (my_position > line_size) {
            my_position = 1;
            std::cout << std::endl;
        }
    }
};

int main()
{
    Machine machine;

    for (std::string line; std::getline(std::cin, line);) {
        machine.process_line(line);
    }

    std::cout << std::endl;

    return 0;
}