//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

class Part2 : public Part1
{
protected:
    static constexpr size_t message_start = 14;

public:
    int Feed(const std::string &line) override
    {
        // use message_start to override default value of package_start.
        auto result = package_decoder(line, message_start);
        if (result == 0) {
            return -1;
        }
        m_result.push_back(result);
        return 0;
    }
};

#endif //INC_2022_PART_2_HPP
