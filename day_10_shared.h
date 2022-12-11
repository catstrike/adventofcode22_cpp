#ifndef __DAY_10_SHARED_H__
#define __DAY_10_SHARED_H__

#include <stdexcept>
#include <charconv>
#include <memory>

#include <optional>

struct ICommand
{
    virtual bool is_finished() = 0;
    virtual void tick() = 0;
};

struct MachineState
{
    int x {1};
};

class NoopCommand : public ICommand
{
    int my_cycles_left {1};

public:
    virtual bool is_finished()
    {
        return my_cycles_left == 0;
    }

    virtual void tick()
    {
        if (my_cycles_left == 0) {
            throw std::invalid_argument("Command execution is finished");
        }

        my_cycles_left--;
    }
};

class AddxCommand : public ICommand
{
    int my_cycles_left {2};

    int my_value;
    MachineState* my_state;

public:
    AddxCommand(int value, MachineState* state)
        : my_value(value)
        , my_state(state)
    {

    }

public:
    virtual bool is_finished()
    {
        return my_cycles_left == 0;
    }

    virtual void tick()
    {
        if (my_cycles_left == 0) {
            throw std::invalid_argument("Command execution is finished");
        }

        my_cycles_left--;

        if (is_finished()) {
            my_state->x += my_value;
        }
    }
};

class MachineBase
{
protected:
    MachineState my_state;
    int my_total_ticks {0};

public:
    void process_line(const std::string& line)
    {
        auto separator = line.find(' ');

        std::string command_name;
        std::optional<int> value;

        if (separator != std::string::npos) {
            int v {0};

            if (std::from_chars(
                line.c_str() + separator + 1,
                line.c_str() + line.size(),
                v
            ).ec != std::errc()) {
                throw new std::invalid_argument("Bad number");
            }

            value = v;
            command_name = line.substr(0, separator);
        } else {
            command_name = line;
        }

        
        std::unique_ptr<ICommand> command;

        if (command_name == "noop") {
            command = std::make_unique<NoopCommand>();
        } else if (command_name == "addx") {
            if (!value.has_value()) {
                throw new std::invalid_argument("addx expect 1 parameter");
            }

            command = std::make_unique<AddxCommand>(*value, &my_state);
        }

        while(!command->is_finished()) {
            my_total_ticks += 1;

            on_tick();

            command->tick();
        }
    }

private:
    virtual void on_tick()
    {
        
    }
};

#endif // __DAY_10_SHARED_H__