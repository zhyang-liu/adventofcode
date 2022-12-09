//
// Created by zhongyang on 2022/12/10.
//

#ifndef INC_2022_9_ACTION_HPP
#define INC_2022_9_ACTION_HPP

#include "direction.hpp"
#include "../common/utils.h"

#include <string>

class action_t
{
    direction_e m_direction_e;
    int         m_count;

public:
    direction_e GetDirection() const { return m_direction_e; }

    int GetCount() const { return m_count; }

    static action_t ParseAction(const std::string &line)
    {
        auto count = (int) ParseInt64(line.substr(2));

        switch (line[0]) {
            case 'R':
                return {direction_e::r, count};
            case 'D':
                return {direction_e::d, count};
            case 'U':
                return {direction_e::u, count};
            case 'L':
                return {direction_e::l, count};
            default:
                return {direction_e::invalid, 0};
        }
    }

protected:
    action_t(direction_e dir, int move_count)
            : m_direction_e(dir), m_count(move_count) {}
};

#endif //INC_2022_9_ACTION_HPP
