#include <iostream>
#include <istream>

#include "day_05_shared.h"

struct MoveCommand : ICommand
{
    const int source;
    const int target;
    const int count;

    MoveCommand(int source, int target, int count)
        : source(source)
        , target(target)
        , count(count)
    {}

    virtual void apply(VectorOfCrateStacks& stacks)
    {
        auto& stack_source = stacks[source - 1];
        auto& stack_target = stacks[target - 1];

        for (int i = 0; i < count; i += 1) {
            auto value = stack_source.back();
            stack_source.pop_back();
            stack_target.push_back(value);
        }
    }
};

static MoveCommand parse_move_parameters(const std::string& line)
{
    int position = 0;
    auto count = *get_next_int(line, position);
    auto source = *get_next_int(line, position);
    auto target = *get_next_int(line, position);

    return MoveCommand(
        source, 
        target,
        count
    );
}


int main()
{
    auto& input = std::cin;
    auto picture = load_picture(input);

    int index = 1;

    for (std::string line; std::getline(input, line);) {
        std::string::size_type parameters_offset;
        auto [command_id, parameters] = read_command(line);

        if (command_id == CommandMove) {
            auto move_command = parse_move_parameters(parameters);
            move_command.apply(picture);
        }
    }

    for (auto& stack : picture) {
        std::cout << stack.back();
    }

    std::cout << std::endl;

    return 0;
}