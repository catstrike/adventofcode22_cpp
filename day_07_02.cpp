#include <iostream>

#include "day_07_shared.h"

int main()
{
    Context context;

    for (std::string line; std::getline(std::cin, line);) {
        context.add_line(line);
    }

    const int total_disk_space = 70000000;
    const int required_for_update = 30000000;
    const int space_used = context.root_folder()->size();
    const int extra_space_required = required_for_update - (total_disk_space - space_used);

    if (extra_space_required < 0) {
        std::cout << "Have enough disk space for update" << std::endl;
        return 0;
    }

    int result = space_used;

    std::stack<IFolderNode*> stack;
    stack.push(context.root_folder());

    while (!stack.empty()) {
        auto folder = stack.top();
        stack.pop();

        int size = folder->size();

        if (size >= extra_space_required && size < result) {
            result = size;
        }

        for (auto [name, node] : *folder) {
            if (node->type() != Folder) continue;

            stack.push(static_cast<IFolderNode*>(node));
        }
    }

    std::cout << result << std::endl;
}