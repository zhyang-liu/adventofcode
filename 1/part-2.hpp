//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

#include <deque>

class Part2 : public Part1
{
protected:
    std::deque<size_t> m_top_3;

public:
    int Feed(const std::string &line) override
    {
        auto prev_max = m_max;
        int  r        = Part1::Feed(line);
        if (r != 0) {
            return r;
        }
        if (prev_max != m_max) {
            // max updated
            pushNewMax(m_max);
        }
        return 0;
    }

    void PrintResult() const override
    {
        Part1::PrintResult();

        size_t          sum = 0;
        for (const auto &item : m_top_3) {
            sum += item;
        }

        printf("%zu\n", sum);
    }

protected:
    void pushNewMax(size_t new_max)
    {
        m_top_3.push_back(new_max);
        if (m_top_3.size() > 3) {
            m_top_3.pop_front();
        }
    }
};

#endif //INC_2022_PART_2_HPP
