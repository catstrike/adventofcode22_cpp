#include <iostream>
#include <stdexcept>

#include <string>
#include <queue>

#include "day_10_shared.h"


class Machine : public MachineBase
{
    int my_signal_strengths_sum {0};
    std::queue<int> my_ticks_of_interest;

public:
    Machine()
    {
        my_ticks_of_interest.push(20);
        my_ticks_of_interest.push(60);
        my_ticks_of_interest.push(100);
        my_ticks_of_interest.push(140);
        my_ticks_of_interest.push(180);
        my_ticks_of_interest.push(220);
    }

public:
    int get_signal_strengths_sum()
    {
        return my_signal_strengths_sum;
    }

private:
    virtual void on_tick()
    {
        if (my_ticks_of_interest.empty()) return;

        if (my_total_ticks == my_ticks_of_interest.front()) {
            my_ticks_of_interest.pop();

            my_signal_strengths_sum += my_total_ticks * my_state.x;
        }
    }
};

int main()
{
    Machine machine;

    for (std::string line; std::getline(std::cin, line);) {
        machine.process_line(line);
    }

    std::cout << machine.get_signal_strengths_sum() << std::endl;

    return 0;
}