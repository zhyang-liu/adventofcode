//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

class Part2 : public Part1 {
public:
    int Feed(const std::string &line) override {
        auto round = splitStrategy(line);

        m_score += getScore(round.first, getOurs(round.first, round.second));
        return 0;
    }

protected:
    static char getOurs(char opponent, char strategy) {
        return strategy_map[opponent][strategy];
    }

    static std::map<char, std::map<char, char>> strategy_map;
};

// A for Rock, B for Paper, and C for Scissors.
// X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win. Good luck!"
// X for Rock, Y for Paper, and Z for Scissors
std::map<char, std::map<char, char>> Part2::strategy_map = {
        {'A',
                {{'X', 'Z'},
                        {'Y', 'X'},
                        {'Z', 'Y'},}
        },
        {'B',
                {{'X', 'X'},
                        {'Y', 'Y'},
                        {'Z', 'Z'},}
        },
        {'C',
                {{'X', 'Y'},
                        {'Y', 'Z'},
                        {'Z', 'X'},}
        },
};

#endif //INC_2022_PART_2_HPP
