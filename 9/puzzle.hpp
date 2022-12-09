//
// Created by zhongyang on 2022/12/9.
//

#ifndef INC_2022_PUZZLE_HPP
#define INC_2022_PUZZLE_HPP

#include <map>
#include <utility>

class puzzle_t
{
protected:
    size_t                            m_count = 0;
    std::map<int, std::map<int, int>> m_marks;

public:
    size_t getMarkCount() const
    {
        return m_count;
    }

    void Mark(int x, int y)
    {
        if (m_marks[x][y]++ == 0) {
            ++m_count;
        }
    }
};

#endif //INC_2022_PUZZLE_HPP
