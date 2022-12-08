//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

class Part2 : public Part1 {
public:
    explicit Part2(size_t n) : Part1(n) {}

protected:
    // the only function we need to override is the way we move crates.
    // just like the difference between CrateMover 9000 and 9001
    int doMovement(const std::string &line) override {
        auto action = action_t::parse(line);
        if (!action.is_valid()) {
            printf("action is not valid: %s\n", line.c_str());
            return 1;
        }

        auto &from = m_stacks[action.from - 1];
        auto &to = m_stacks[action.to - 1];

        to += from.substr(from.length() - action.count);
        from.erase(from.length() - action.count);

        return 0;
    }
};

#endif //INC_2022_PART_2_HPP
