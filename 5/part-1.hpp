//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

#include <iostream>
#include <deque>
#include <vector>

struct action_t
{
    size_t count;
    size_t from;
    size_t to;

    bool is_valid() const
    {
        return count && from && to;
    }

    static action_t parse(const std::string &line)
    {
        // move 1 from 1 to 2
        const char *begin = line.c_str() + strlen("move ");
        char       *end   = nullptr;
        action_t   action = {0, 0, 0};

        action.count = strtoul(begin, &end, 10);
        if (*end != ' ') {
            // parse failed
            return action_t{0, 0, 0};
        }

        begin = end + strlen("from ");
        action.from = strtoul(begin, &end, 10);
        if (*end != ' ') {
            // parse failed
            return action_t{0, 0, 0};
        }

        begin = end + strlen("to ");
        action.to = strtoul(begin, &end, 10);
        if (*end != '\0') {
            // parse failed
            return action_t{0, 0, 0};
        }

        return action;
    }
};

class Part1 : public LineProcessor
{
protected:
    typedef std::string crate_stack_t;

    std::vector<crate_stack_t> m_stacks;
    bool                       m_header_loaded = false;

public:
    // My IDE drops tailing spaces, from which the number of stacks could be easily calculated.
    // I don't want to look backward to detect how many stacks there is.
    // Thus, I use an argument to pass the number of stacks directly.
    explicit Part1(size_t n_stacks)
            : m_stacks(n_stacks)
    {
    }

    int Feed(const std::string &line) override
    {
        if (line.empty()) {
            return 0;
        } else if (!m_header_loaded) {
            return parseHeader(line);
        }
        return doMovement(line);
    }

    void PrintResult() const override
    {
        std::string result;
        for (auto   iter : m_stacks) {
            result += *iter.rbegin();
        }
        printf("message: %s\n", result.c_str());
    }

protected:
    void printStack() const
    {
        size_t          n = 1;
        for (const auto &iter : m_stacks) {
            if (iter.empty()) {
                continue;
            }
            std::cout << n << ": ";
            for (auto c : iter) {
                std::cout << c;
            }
            std::cout << std::endl;
            ++n;
        }
        printf("-----\n");
    }

    // header parsing is not elegant, but it's good enough for the scenario.
    int parseHeader(const std::string &line)
    {
        // check if line begins with "[X]" or "    [X]"
        if (line[0] == '[' || line[1] == ' ') {
            // this is a crate line
            return loadStacks(line);
        } else if (HasPrefix(line, " 1")) {
            m_header_loaded = true;
            printStack();
            return 0;
        } else {
            printf("invalid line fed: %s\n", line.c_str());
            return 1;
        }
    }

    // doMovement makes the actual movement and will be overridden in part 2.
    virtual int doMovement(const std::string &line)
    {
        auto action = action_t::parse(line);
        if (!action.is_valid()) {
            printf("action is not valid: %s\n", line.c_str());
            return 1;
        }

        auto &from = m_stacks[action.from - 1];
        auto &to   = m_stacks[action.to - 1];

        for (size_t i = 0; i < action.count; ++i) {
            to += *from.rbegin();
            from.pop_back();
        }
        printStack();
        return 0;
    }

    int loadStacks(std::string line)
    {
        size_t n = 0;
        while (!line.empty()) {
            if (line[1] != ' ') {
                m_stacks[n].insert(m_stacks[n].begin(), line[1]);
            }
            n++;

            // [X]
            if (line.length() > 3) {
                line = line.substr(4);
            } else {
                line.clear();
            }
        }
        return 0;
    }
};

#endif //INC_2022_PART_1_HPP
