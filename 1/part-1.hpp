//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

class Part1 : public LineProcessor {
protected:
    size_t m_max;
    size_t m_elf;

public:
    explicit Part1() : m_max(0), m_elf(0) {}

    int Feed(const std::string &line) override {
        if (line.empty()) {
            if (m_elf > m_max) {
                m_max = m_elf;
            }
            m_elf = 0;
            return 0;
        }

        m_elf += ParseString(line);

        return 0;
    }

    void PrintResult() const override {
        printf("%zu\n", m_max);
    }

public:
    static size_t ParseString(const std::string &value) {
        char *end = nullptr;
        size_t result = strtoul(value.c_str(), &end, 10);
        if (end && (*end == 0)) {
            return result;
        }
        return 0;
    }
};


#endif //INC_2022_PART_1_HPP
