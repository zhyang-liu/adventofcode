//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

#include <iostream>
#include <unordered_map>

class Part1 : public LineProcessor {
protected:
    size_t m_priority_sum = 0;

public:
    int Feed(const std::string &line) override {
        m_priority_sum += findDuplicate(line);
        return 0;
    }

    void PrintResult() const override {
        std::cout << m_priority_sum << std::endl;
    }

protected:
    static size_t findDuplicate(const std::string &line) {
        bool checker_map[53] = {false}; // skip first char due to priority starts with 1
        for (size_t i = 0; i < line.length() / 2; ++i) {
            checker_map[getPriority(line[i])] = 1;
        }

        for (size_t i = line.length() / 2; i < line.length(); ++i) {
            if (checker_map[getPriority(line[i])]) {
                return getPriority(line[i]);
            }
        }
    }

    static size_t getPriority(char c) {
        if (std::islower(c)) {
            return c - 'a' + 1;
        } else if (std::isupper(c)) {
            return c - 'A' + 27;
        }
        return 0;
    }
};


#endif //INC_2022_PART_1_HPP
