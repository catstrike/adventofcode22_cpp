#include <iostream>

#include "day_07_shared.h"

int main()
{
    Context context;

    for (std::string line; std::getline(std::cin, line);) {
        context.add_line(line);
    }

    const int max_size = 100000;

    int result {0};

    std::stack<IFolderNode*> stack;
    stack.push(context.root_folder());

    while (!stack.empty()) {
        auto folder = stack.top();
        stack.pop();

        int size = folder->size();

        if (size <= max_size) {
            result += size;
        }

        for (auto [name, node] : *folder) {
            if (node->type() != Folder) continue;

            stack.push(static_cast<IFolderNode*>(node));
        }
    }

    std::cout << result << std::endl;
}