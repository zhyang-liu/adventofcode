//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

class Part1 : public LineProcessor
{
protected:
    typedef std::pair<uint8_t, uint8_t> group_t;

    size_t m_full_contain_count = 0;

public:
    int Feed(const std::string &line) override
    {
        group_t a, b;
        int     r = parseLine(line, &a, &b);
        if (r != 0) {
            return r;
        }

        // use containsLater for part 1 and overlapsLater for part 2
        if (overlapsLater(a, b) || overlapsLater(b, a)) {
            ++m_full_contain_count;
        }

        return 0;
    }

    void PrintResult() const override
    {
        printf("%zu\n", m_full_contain_count);
    }

protected:
    // part 1
    static bool containsLater(const group_t &a, const group_t &b)
    {
        return (b.first >= a.first) && (b.second <= a.second);
    }

    // part 2
    static bool overlapsLater(const group_t &a, const group_t &b)
    {
        return (a.first >= b.first && a.first <= b.second) || (a.second >= b.first && a.second <= b.second);
    }

    static int parseLine(const std::string &line, group_t *a, group_t *b)
    {
        // 2-4,6-8
        char       *end = nullptr;
        const char *h   = line.c_str();

        a->first = strtoul(h, &end, 10);
        if (*end != '-') {
            return 1;
        }

        h   = end + 1;
        end = nullptr;
        a->second = strtoul(h, &end, 10);
        if (*end != ',') {
            return 2;
        }

        h   = end + 1;
        end = nullptr;
        b->first = strtoul(h, &end, 10);
        if (*end != '-') {
            return 3;
        }

        h   = end + 1;
        end = nullptr;
        b->second = strtoul(h, &end, 10);
        if (*end != 0) {
            return 4;
        }

        return 0;
    }
};

#endif //INC_2022_PART_1_HPP
