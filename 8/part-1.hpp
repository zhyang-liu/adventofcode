//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "../common/utils.h"

#include <iostream>
#include <deque>
#include <vector>

class Part1 : public LineProcessor
{
protected:
    typedef std::vector<char>              row_t;
    typedef std::vector<std::vector<char>> forest_t;

    forest_t m_forest;
    row_t    m_highest_by_row;
    row_t    m_highest_by_col;

    mutable forest_t m_visit_times;

public:
    int Feed(const std::string &line) override
    {
        // to enlarge the size at first time.
        // both .size() and .length() is constant time complicity,
        // thus it won't slow down the feeding procedure.
        if (m_highest_by_col.size() < line.length()) {
            m_highest_by_col.resize(line.length(), -1);
        }

        row_t  row(line.length());
        size_t i           = 0;
        char   row_highest = -1;

        for (const auto c : line) {
            auto h = (char) (c - '0');
            if (h > row_highest) {
                row_highest = h;
            }
            row[i] = h;

            // update the highest in column
            if (h > m_highest_by_col[i]) {
                m_highest_by_col[i] = h;
            }
            ++i;
        }

        m_forest.emplace_back(row);
        m_visit_times.emplace_back(row.size(), 0);
        m_highest_by_row.push_back(row_highest);
        return 0;
    }

    void PrintResult() const override
    {
        std::cout << checkForest() << std::endl;
    }

protected:
    size_t checkForest() const
    {
        row_t  col_second_highest(m_highest_by_col.size(), -1);
        size_t visible_count = 0;

        // 1st round: top to down
        // printf("top to down\n");
        for (size_t r = 0; r < m_forest.size(); ++r) {
            const auto &row           = m_forest[r];
            size_t     column_visible = 0;

            // printRow(row);
            // printf("checking row %zu, highest in row is %d\n", r, m_highest_by_row[r]);

            for (size_t c = 0; c < row.size(); ++c) {
                if (row[c] > col_second_highest[c]) {
                    if (m_visit_times[r][c]++ == 0) {
                        ++column_visible;
                    }
                    col_second_highest[c] = row[c];
                    // printf(" %d is visible on column [%zu]\n", row[c], c);
                }
            }

            // check row in the first pass
            auto row_visible = checkRow(row, m_highest_by_row[r], &m_visit_times[r]);
            visible_count += (column_visible + row_visible);
            // printf("adding (%zu + %zu), total: %zu\n", column_visible, row_visible, visible_count);
        }

        // 2nd round: down to top;
        // clean up
        col_second_highest.clear();
        col_second_highest.resize(m_highest_by_col.size(), -1);

        // start iteration
        // printf("down to top\n");
        for (auto row_iter = m_forest.rbegin(); row_iter != m_forest.rend(); ++row_iter) {
            auto &row = *row_iter;
            auto r    = m_forest.size() - (row_iter - m_forest.rbegin() + 1);

            for (size_t c = 0; c < row.size(); ++c) {
                if (row[c] > col_second_highest[c]) {
                    // printf("%d is visible at [%zu][%zu]", row[c], r, c);
                    if (m_visit_times[r][c]++ == 0) {
                        ++visible_count;
                    } else {
                        // printf(", seen before");
                    }
                    // printf("\n");
                    col_second_highest[c] = row[c];
                }
            }
        }

        return visible_count;
    }


    static size_t checkRow(const row_t &row, const uint8_t highest, row_t *visible_marks)
    {
        char   second_highest = -1;
        size_t visible_count  = 0;

        // from left to right
        // printf(" from left to right:");
        for (size_t c = 0; c < row.size(); ++c) {
            auto height = row[c];

            if (height > second_highest) {
                // printf(" %d", height);
                if ((*visible_marks)[c]++ == 0) {
                    ++visible_count;
                } else {
                    // printf("(%d)", (*visible_marks)[c]);
                }
                second_highest = height;
            }

            if (height == highest) {
                break;
            }
        }
        // printf("\n");

        // from right to left
        second_highest = -1;
        // printf(" from right to left:");
        for (auto iter = row.rbegin(); iter != row.rend(); ++iter) {
            auto &height = *iter;
            auto c       = row.size() - (iter - row.rbegin() + 1);

            if (height > second_highest) {
                // printf(" %d", height);
                if ((*visible_marks)[c]++ == 0) {
                    ++visible_count;
                } else {
                    // printf("(%d)", (*visible_marks)[c]);
                }
                second_highest = height;
            }

            if (height == highest) {
                break;
            }
        }
        // printf("\n");

        return visible_count;
    }

    static void printRow(const row_t &row)
    {
        printf("row: ");
        for (auto h : row) {
            printf("%d", h);
        }
        printf("\n");
    }
};

#endif //INC_2022_PART_1_HPP
