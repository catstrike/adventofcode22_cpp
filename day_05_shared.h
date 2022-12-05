#ifndef __DAY_05_SHARED_H__
#define __DAY_05_SHARED_H__

#include <stdexcept>
#include <charconv>
#include <istream>

#include <string>
#include <optional>
#include <vector>
#include <deque>
#include <tuple>

using CrateStack = std::deque<char>;
using VectorOfCrateStacks = std::vector<CrateStack>;

const std::string DIGITS = "0123456789";

enum CommandType {
    CommandUnknown,
    CommandMove
};

struct ICommand
{
    virtual void apply(VectorOfCrateStacks& stacks) = 0;
};

static std::optional<std::tuple<int, char>> get_next_crate(const std::string& line, int& offset)
{
    int position = offset;

    if ((position = line.find('[', position)) == std::string::npos) {
        return std::nullopt;
    }

    if (position + 2 >= line.size()) {
        return std::nullopt;
    }

    char crate_id = line[position + 1];

    offset = position + 2;

    return std::make_tuple(
        position / 4,
        crate_id
    );
}

static void apply_line(VectorOfCrateStacks& crates, const std::string& line) 
{
    std::optional<std::tuple<int, char>> crate;

    for (int position = 0; crate = get_next_crate(line, position);) {
        auto [n, id] = *crate;

        if (n < 0 || n >= crates.size()) {
            throw new std::invalid_argument("Index out of range");
        }

        crates[n].push_front(id);
    }
}

static bool is_empty(const std::string& line)
{
    return line.empty() || line.size() == 1;
}

static VectorOfCrateStacks load_picture(std::basic_istream<char>& input)
{
    std::string line;

    if (!std::getline(input, line)) {
        throw new std::invalid_argument("Bad input");
    }

    int number_of_crates = (line.size() + 1) / 4;

    VectorOfCrateStacks crates(number_of_crates);

    do {
        apply_line(crates, line);
    } while (std::getline(input, line) && !is_empty(line));

    return crates;
}

static std::tuple<CommandType, std::string> read_command(const std::string& line)
{
    auto separator = line.find(' ');
    std::string parameters;

    if (separator != std::string::npos && separator + 1 < line.size()) {
        parameters = line.substr(separator + 1);
    }

    std::string_view command(line.c_str(), separator);

    CommandType command_type = CommandUnknown;

    if (command == "move") {
        command_type = CommandMove;
    }

    return std::make_tuple(command_type, parameters);
}

std::optional<int> get_next_int(const std::string& line, int& position)
{
    auto begin = line.find_first_of(DIGITS, position);

    if (begin == std::string::npos) {
        return std::nullopt;
    }

    auto end = line.find_first_not_of(DIGITS, begin);

    if (end == std::string::npos) {
        end = line.size();
    }

    position = end;

    int value;

    std::from_chars(
        line.c_str() + begin,
        line.c_str() + end,
        value
    );

    return value;
}

#endif // __DAY_05_SHARED_H__