//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "struct-node.hpp"
#include "struct-command.hpp"
#include "../common/utils.h"
#include <iostream>

class Part1 : public LineProcessor
{
protected:
    enum class state_e : size_t
    {
        none = 0,
        ls   = 1,
        cd   = 2,
    };

    state_e m_state        = state_e::none;
    Node    *m_root        = Node::NewRoot();
    Node    *m_current_dir = m_root;

public:
    int Feed(const std::string &line) override
    {
        if (isCommand(line)) {
            return parseAndProcessCommand(line);
        }

        switch (m_state) {
            case state_e::ls: {
                return processLsResult(line);
            }
            case state_e::cd:
                fprintf(stderr, "expecting command with leading \"$ \", got \"%s\"\n", line.c_str());
                return 1;
            default:
                fprintf(stderr, "unexpected line %s\n", line.c_str());
                return 1;
        }
    }

    void PrintResult() const override
    {
        constexpr size_t threshold = 100000;
        size_t           sum       = 0;

        m_root->Walk([&](const Node *node)
                     {
                         if (node->IsDir()) {
                             auto node_size = node->GetSize();
                             if (node_size <= threshold) {
                                 sum += node_size;
                             }
                         }
                     });
        std::cout << sum << std::endl;
    }

protected:
    int parseAndProcessCommand(const std::string &line)
    {
        auto command = Command::ParseCommand(line);
        if (!command.IsValid()) {
            fprintf(stderr, "invalid command: \"%s\"\n", line.c_str());
            return 1;
        }
        return processCommand(command);
    }

    int processCommand(const Command &command)
    {
        switch (command.GetType()) {
            case Command::Type::Cd: {
                m_state = state_e::cd;

                if (command.GetSubject() == "/") {
                    m_current_dir = m_root;
                    return 0;
                } else if (command.GetSubject() == "..") {
                    m_current_dir = m_current_dir->GetParent();
                    return 0;
                }
                auto child = m_current_dir->GetChild(command.GetSubject());
                if (child && child->IsDir()) {
                    m_current_dir = child;
                    return 0;
                }
                fprintf(stderr, "element %s is not directory.\n", command.GetSubject().c_str());
                return 1;
            }
            case Command::Type::Ls:
                m_state = state_e::ls;
                return 0;

            case Command::Type::None:
            default:
                fprintf(stderr, "invalid command %zu\n", (size_t) command.GetType());
                return 1;
        }
    }

    int processLsResult(const std::string &line)
    {
        if (HasPrefix(line, "dir ")) {
            m_current_dir->AddChild(Node::NewDir(TrimSpaces(line.substr(4))));
            return 0;
        }

        size_t bytes_read = 0;
        auto   file_size  = ParseInt64(line, &bytes_read);

        m_current_dir->AddChild(Node::NewFile(TrimSpaces(line.substr(bytes_read)), file_size));
        return 0;
    }

    static bool isCommand(const std::string &line)
    {
        return HasPrefix(line, "$ ");
    }
};

#endif //INC_2022_PART_1_HPP
