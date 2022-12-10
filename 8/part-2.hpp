//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

class Part2 : public Part1
{
protected:
    typedef std::pair<size_t, size_t> spot_t;

public:
    void PrintResult() const override
    {
        // printf("visit times:\n");
        // for (const auto &row : m_visit_times) {
        //     for (const auto &c : row) {
        //         printf("% 3d", c);
        //     }
        //     printf("\n");
        // }
        // printf("forest:\n");
        // for (const auto &row : m_forest) {
        //     for (const auto &c : row) {
        //         printf("% 3d", c);
        //     }
        //     printf("\n");
        // }

        int score = 0;

        for (auto r = 1; r < m_forest.size() - 1; ++r) {
            for (auto c = 1; c < m_forest[r].size() - 1; ++c) {
                auto s = scoreSpot(std::make_pair(r, c));
                if (s > score) {
                    score = s;
                }
            }
        }
        printf("score: %d\n", score);
    }

protected:
    int scoreSpot(const spot_t &spot) const
    {
        // stop if you reach an edge
        // or at the first tree that is the same height or taller than the tree under consideration
        char limit = m_forest[spot.first][spot.second];

        int u = scoreUp(spot, limit);
        int d = scoreDown(spot, limit);
        int l = scoreLeft(spot, limit);
        int r = scoreRight(spot, limit);
        int f = u * d * l * r;

        // printf("  (%zu,%zu) [%d] u: %d, d: %d, l: %d, r: %d, final: %d\n",
        //        spot.first, spot.second, m_forest[spot.first][spot.second], u, d, l, r, f);

        return f;
    }

    int scoreUp(const spot_t &spot, char limit) const
    {
        int score = 0;

        // to up
        for (auto i = (ssize_t) spot.first - 1; i >= 0; --i) {
            ++score;
            if (m_forest[i][spot.second] >= limit) {
                break;
            }
        }

        return score;
    }

    int scoreDown(const spot_t &spot, char limit) const
    {
        int score = 0;

        // to down
        for (auto i = (ssize_t) spot.first + 1; i < m_forest.size(); ++i) {
            ++score;
            if (m_forest[i][spot.second] >= limit) {
                break;
            }
        }

        return score;
    }

    int scoreLeft(const spot_t &spot, char limit) const
    {
        int score = 0;

        // to left
        for (auto i = (ssize_t) spot.second - 1; i >= 0; --i) {
            ++score;
            if (m_forest[spot.first][i] >= limit) {
                break;
            }
        }

        return score;
    }

    int scoreRight(const spot_t &spot, char limit) const
    {
        int score = 0;

        // to right
        for (auto i = (ssize_t) spot.second + 1; i < m_forest.size(); ++i) {
            ++score;
            if (m_forest[spot.first][i] >= limit) {
                break;
            }
        }

        return score;
    }
};

#endif //INC_2022_PART_2_HPP
