#ifndef __DAY_07_SHARED_H__
#define __DAY_07_SHARED_H__

#include <stdexcept>

#include <unordered_map>
#include <stack>
#include <string>

extern const std::invalid_argument unexpected_parameter("Unexpected parameter");
extern const std::string DIR = "dir";
extern const std::string LS_COMMAND = "ls";
extern const std::string CD_COMMAND = "cd";

enum NodeType
{
    Folder,
    File
};

struct IFolderNode;

struct IContext
{
    virtual IFolderNode* current_folder() const = 0;
    virtual void set_current_folder(IFolderNode* folder) = 0;
    virtual IFolderNode* root_folder() const = 0;
};

struct ICommand
{
    virtual void begin(const std::string& parameters) = 0;
    virtual void add_parameter(const std::string& line) = 0;
};

struct INode
{
    virtual ~INode() {};

    virtual NodeType type() const = 0;
    virtual int size() const = 0;
};

struct IFolderNode : public INode
{
    using nodes_map = std::unordered_map<std::string, INode*>;
    using iterator = nodes_map::iterator;

    virtual void add_node(std::string name, INode* node) = 0;
    virtual INode* get_node(std::string name) const = 0;
    virtual IFolderNode* parent() const = 0;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;
};

class FileNode : public INode
{
    int my_file_size;
public: // - Lifecycle
    FileNode(int file_size)
        : my_file_size(file_size) 
    {}

public: // - Public

    virtual NodeType type() const { return File; }
    virtual int size() const { return my_file_size; }
};

class FolderNode : public IFolderNode
{
    nodes_map my_nodes;
    IFolderNode* my_parent;

public:
    FolderNode(IFolderNode* parent) : my_parent(parent) {}

    virtual ~FolderNode()
    {
        for (auto [_, node] : my_nodes) {
            delete node;
        }
    }

public: // - Iterator
    virtual iterator begin() { return std::begin(my_nodes); }
    virtual iterator end() { return std::end(my_nodes); }

public: // - Public
    virtual NodeType type() const { return Folder; }
    
    virtual int size() const
    {
        int total_size = 0;

        for (auto [name, node] : my_nodes) {
            total_size += node->size();
        }

        return total_size;
    }

    virtual void add_node(std::string name, INode* node)
    {
        my_nodes[name] = node;
    }

    virtual INode* get_node(std::string name) const
    {
        auto it = my_nodes.find(name);

        if (it == std::end(my_nodes)) {
            throw new std::range_error("Node not found");
        }

        return it->second;
    }

    virtual IFolderNode* parent() const
    {
        return my_parent;
    }
};

class CdCommand : public ICommand
{
    IContext *my_context;

public: // - Lifecycle
    CdCommand(IContext *context) : my_context(context) {}

public: // - Public

    virtual void begin(const std::string& parameters)
    {
        if (parameters == "/") {
            my_context->set_current_folder(
                my_context->root_folder()
            );
            return;
        }

        if (parameters == "..") {
            my_context->set_current_folder(
                my_context->current_folder()->parent()
            );
            return;
        }

        auto node = my_context->current_folder()->get_node(parameters);

        if (node->type() != Folder) {
            throw new std::invalid_argument("The node is not a folder!");
        }

        my_context->set_current_folder(
            static_cast<IFolderNode*>(node)
        );
    }

    virtual void add_parameter(const std::string& line) 
    {
        throw &unexpected_parameter;
    }
};

class LsCommand : public ICommand
{
    IContext *my_context;

public: // - Lifecycle
    LsCommand(IContext *context) : my_context(context) {}

public: // - Public

    virtual void begin(const std::string& parameters)
    {
    }

    virtual void add_parameter(const std::string& line) 
    {
        auto folder = my_context->current_folder();

        auto name_separator = line.find(' ');

        if (name_separator == std::string::npos) {
            throw new std::invalid_argument("Unexpected input");
        }

        auto parameter = line.substr(0, name_separator);
        auto name = line.substr(name_separator + 1);

        if (parameter == DIR) {
            folder->add_node(name, new FolderNode(folder));
            return;
        }

        folder->add_node(
            name,
            new FileNode(std::stoi(parameter))
        );
    }
};

class Context : public IContext
{
    IFolderNode* my_root;
    IFolderNode* my_current_folder;
    ICommand* my_current_command;

public: // - Lifecycle
    Context()
        : my_current_command(nullptr)
    {
        my_root = new FolderNode(nullptr);
        my_current_folder = my_root;
    }

    ~Context()
    {
        delete my_root;
        // don't delete my_current_folder because it should be deleted by deleting my_root
        delete my_current_command;
    }

public: // - Public
    void add_line(const std::string& line)
    {
        if (line[0] != '$') {
            if (my_current_command == nullptr) {
                throw &unexpected_parameter;
            }

            my_current_command->add_parameter(line);
            return;
        }

        delete my_current_command;

        int begin = 2;
        int end = line.find(' ', begin);

        if (end == std::string::npos) {
            my_current_command = process_command(line.substr(begin), "");
        } else {
            my_current_command = process_command(
                line.substr(begin, end - begin),
                line.substr(end + 1)
            );
        }
    }

    virtual IFolderNode* current_folder() const { return my_current_folder; }

    virtual void set_current_folder(IFolderNode* folder)
    {
        my_current_folder = folder;
    }

    virtual IFolderNode* root_folder() const { return my_root; }

private: // - Private
    ICommand* process_command(std::string command_name, std::string parameters)
    {
        ICommand* command;

        if (command_name == LS_COMMAND) {
            command = new LsCommand(this);
        } else if (command_name == CD_COMMAND) {
            command = new CdCommand(this);
        } else {
            throw new std::invalid_argument(std::string("Unknown command ") + command_name);
        }

        command->begin(parameters);

        return command;
    }
};

#endif // __DAY_07_SHARED_H__