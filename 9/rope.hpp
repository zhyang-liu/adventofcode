//
// Created by zhongyang on 2022/12/9.
//

#ifndef INC_2022_ROPE_HPP
#define INC_2022_ROPE_HPP

#include "direction.hpp"
#include "puzzle.hpp"

#include <vector>

class node_t;


class node_t
{
public:
    node_t(puzzle_t *puzzle, int x, int y)
            : m_puzzle(puzzle), m_x(x), m_y(y)
    {
    }

    node_t *Append(node_t *next)
    {
        this->m_next = next;
        next->m_prev = this;

        return next;
    }

    node_t *GetNext() const
    {
        return m_next;
    }

    std::pair<int, int> GetPos() const
    {
        return std::make_pair(m_x, m_y);
    }

    bool IsNearBy(node_t *other) const
    {
        auto h = std::abs(m_x - other->m_x);
        auto v = std::abs(m_y - other->m_y);
        return (h <= 1) && (v <= 1);
    }

    void Move(direction_e direction)
    {
        switch (direction) {
            case direction_e::u:
                ++m_y;
                break;

            case direction_e::r:
                ++m_x;
                break;

            case direction_e::l:
                --m_x;
                break;

            case direction_e::d:
                --m_y;
                break;

            case direction_e::ur:
                Move(direction_e::u);
                Move(direction_e::r);
                break;

            case direction_e::dr:
                Move(direction_e::d);
                Move(direction_e::r);
                break;

            case direction_e::ul:
                Move(direction_e::u);
                Move(direction_e::l);
                break;

            case direction_e::dl:
                Move(direction_e::d);
                Move(direction_e::l);
                break;

            default:
            case direction_e::cover:
            case direction_e::invalid:
                break;
        }
    }

    void Mark()
    {
        m_puzzle->Mark(m_x, m_y);
    }

    // getDirection reports the direction from current to prev.
    static direction_e GetDirection(const node_t *current, const node_t *prev)
    {
        if ((current == nullptr) || (prev == nullptr)) {
            return direction_e::invalid;
        }

        direction_e direction = direction_e::cover;
        if (prev->m_x > current->m_x) {
            direction |= direction_e::r;
        } else if (prev->m_x < current->m_x) {
            direction |= direction_e::l;
        }

        if (prev->m_y > current->m_y) {
            direction |= direction_e::u;
        } else if (prev->m_y < current->m_y) {
            direction |= direction_e::d;
        }

        return direction;
    }

protected:
    // x means the horizontal and y means vertical.
    // the left bottom corner is 0.
    int m_x = 0;
    int m_y = 0;

    puzzle_t *m_puzzle = nullptr;
    node_t   *m_prev   = nullptr;
    node_t   *m_next   = nullptr;

    direction_e getPrevDirection() const
    {
        return GetDirection(this, m_prev);
    }
};

class rope_t
{
protected:
    node_t   *m_head   = nullptr;
    puzzle_t *m_puzzle = nullptr;

public:
    rope_t(puzzle_t *puzzle, size_t node_count, int x, int y)
            : m_head(new node_t(puzzle, x, y)), m_puzzle(puzzle)
    {
        auto   *iter = m_head;
        node_t *last = nullptr;

        for (auto i = 1; i < node_count; ++i) {
            last = new node_t(puzzle, x, y);
            iter = iter->Append(last);
        }
        last->Mark();
    }


    ~rope_t()
    {
        auto *iter = m_head;
        while (iter != nullptr) {
            auto next = iter->GetNext();
            delete iter;
            iter = next;
        }
    }

    void Move(direction_e direction)
    {
        auto prev = this->m_head;
        prev->Move(direction);

        auto n = prev->GetNext();
        while (n != nullptr) {
            if (!n->IsNearBy(prev)) {
                direction = node_t::GetDirection(n, prev);
                n->Move(direction);
            }
            prev = n;
            n    = prev->GetNext();
        }
        prev->Mark();
    }

    void PrintRope() const
    {
        for (auto n = m_head; n != nullptr; n = n->GetNext()) {
            auto pos = n->GetPos();
            printf("(%d, %d) ", pos.first, pos.second);
        }
        printf("\n");
    }
};

#endif //INC_2022_ROPE_HPP
