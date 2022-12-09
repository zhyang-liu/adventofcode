//
// Created by zhongyang on 2022/12/9.
//

#ifndef INC_2022_DIRECTION_HPP
#define INC_2022_DIRECTION_HPP

enum class direction_e : unsigned
{
    // we use bit mask to mark basic 4 directions.
    u = (1u << 0),
    l = (1u << 1),
    d = (1u << 2),
    r = (1u << 3),

    ur = u | r,
    dr = d | r,
    ul = u | l,
    dl = d | l,

    cover   = 0, // not anywhere, default to covers
    invalid = ~0u,
};

// append the bitmask
inline direction_e operator|(direction_e l, direction_e r)
{
    return (direction_e) ((unsigned) l | (unsigned) r);
}

inline direction_e operator|=(direction_e &l, direction_e r)
{
    return l = l | r;
}

#endif //INC_2022_DIRECTION_HPP
