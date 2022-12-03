#include <iostream>
#include <string>

int main()
{
    int max {0};

    int elf_max {0};

    for (std::string value; std::getline(std::cin, value);) {
        if (value.empty()) {
            max = std::max(max, elf_max);
            elf_max = 0;
            continue;
        }

        elf_max += std::stoi(value);
    }

    max = std::max(max, elf_max);

    std::cout << max << std::endl;

    return 0;
}