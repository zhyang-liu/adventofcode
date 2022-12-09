//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "action.hpp"
#include "puzzle.hpp"
#include "rope.hpp"

#include "../common/utils.h"

#include <iostream>
#include <deque>
#include <vector>
#include <list>

class Part1 : public LineProcessor
{
protected:
    puzzle_t m_puzzle;
    rope_t   m_rope;

public:
    explicit Part1(size_t rope_length = 2)
            : m_rope(&m_puzzle, rope_length, 0, 0)
    {
    }

    int Feed(const std::string &line) override
    {
        printf("action: %s\n", line.c_str());

        auto action = action_t::ParseAction(line);

        for (int i = 0; i < action.GetCount(); ++i) {
            m_rope.Move(action.GetDirection());
        }

        return 0;
    }

    void PrintResult() const override
    {
        std::cout << m_puzzle.getMarkCount() << std::endl;
    }

protected:
};

#endif //INC_2022_PART_1_HPP
