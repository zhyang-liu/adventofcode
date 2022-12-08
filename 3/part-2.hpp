//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"
#include <map>

class Part2 : public Part1 {
    size_t m_group_checker[53] = {0};
    size_t m_team_member = 0;
    size_t m_line_counter = 0;

public:
    int Feed(const std::string &line) override {
        m_team_member = m_line_counter % 3;
        if (m_team_member == 0) {
            memset(m_group_checker, 0, sizeof(m_group_checker));
        }

        for (const auto &c: line) {
            auto flag = (1u << m_team_member);
            auto p = getPriority(c);

            m_group_checker[p] |= flag;
            if (m_group_checker[p] == 0x07) {
                m_priority_sum += p;
                break;
            }
        }

        ++m_line_counter;
        return 0;
    }
};


#endif //INC_2022_PART_2_HPP
