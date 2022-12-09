//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

#include <map>

class Part1 : public LineProcessor
{
protected:
    size_t m_score = 0;

public:
    int Feed(const std::string &line) override
    {
        auto round = splitStrategy(line);
        m_score += getScore(round.first, round.second);
        return 0;
    }

    void PrintResult() const override
    {
        printf("score: %zu\n", m_score);
    }

protected:
    static std::pair<char, char> splitStrategy(const std::string &line)
    {
        return std::make_pair(line[0], line[2]);
    }

    static size_t getScore(char opponent, char ours)
    {
        return winningScore(opponent, ours) + shapeScore(ours);
    }

    static size_t winningScore(char opponent, char ours)
    {
        return winning_score_map[opponent][ours];
    }

    static size_t shapeScore(char ours)
    {
        return shape_score_map[ours];
    }

    static std::map<char, std::map<char, size_t>> winning_score_map;
    static std::map<char, size_t>                 shape_score_map;
};

// opponent: A for Rock, B for Paper, and C for Scissors.
//       me: X for Rock, Y for Paper, and Z for Scissors.
std::map<char, std::map<char, size_t>> Part1::winning_score_map = {
        {
                'A',
                {{'X', 3},
                        {'Y', 6},
                        {'Z', 0},}
        },
        {
                'B',
                {{'X', 0},
                        {'Y', 3},
                        {'Z', 6},}
        },
        {
                'C',
                {{'X', 6},
                        {'Y', 0},
                        {'Z', 3},}
        },
};

// 1 for Rock, 2 for Paper, and 3 for Scissors
// X for Rock, Y for Paper, and Z for Scissors
std::map<char, size_t> Part1::shape_score_map = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
};

#endif //INC_2022_PART_1_HPP
