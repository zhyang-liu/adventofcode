//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

#include <iostream>
#include <deque>


class Part1 : public LineProcessor {
protected:
    static constexpr size_t package_start = 4;
    std::deque<size_t> m_result;

public:
    int Feed(const std::string &line) override {
        auto result = package_decoder(line);
        if (result == 0) {
            return -1;
        }
        m_result.push_back(result);
        return 0;
    }

    void PrintResult() const override {
        for (auto iter: m_result) {
            std::cout << iter << std::endl;
        }
    }

protected:
    static size_t package_decoder(const std::string &line, size_t diff_decoder = package_start) {
        std::deque<char> dq;
        uint8_t different_counter = 0;
        uint8_t char_counter[26] = {0};

        for (auto i = 0; i < line.length(); ++i) {
            auto c = line[i];

            // check if this char is increasing from 0
            if (char_counter[get_index(c)]++ == 0) {
                ++different_counter;
            }

            dq.push_back(c);
            if (dq.size() < diff_decoder) {
                continue;
            }

            if (different_counter == diff_decoder) {
                return i + 1;
            }

            // check if this char has decreased to 0
            if (--char_counter[get_index(dq.front())] == 0) {
                --different_counter;
            }
            dq.pop_front();
        }
        return 0;
    }

    // we need a deque with size not larger than 3
    static int get_index(char c) {
        return c - 'a';
    }
};

#endif //INC_2022_PART_1_HPP
