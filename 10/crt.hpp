//
// Created by zhongyang on 2022/12/10.
//

#ifndef INC_2022_10_CRT_HPP
#define INC_2022_10_CRT_HPP

#include <vector>
#include <cstdint>
#include <string>

class crt_t
{
protected:
    char   m_screen_buffer[6][40] = {0};
    size_t m_cycle                = 0;

public:
    crt_t()
    {
        memset(m_screen_buffer, '.', sizeof(m_screen_buffer));
    }

    void Tick(int64_t sprite_pos)
    {
        // top-left is (0,0)
        auto screen = (int64_t) ((m_cycle++) % (6 * 40));
        auto line   = screen / 40;
        auto offset = screen % 40;
        // printf("cycle: %zu, line: %lli, offset: %lli, sprite: %lli\n", m_cycle - 1, line, offset, sprite_pos);

        if (abs(sprite_pos - offset) <= 1) {
            m_screen_buffer[line][offset] = '#';
        } else {
            m_screen_buffer[line][offset] = '.';
        }
    }

    void PrintBuffer() const
    {
        for (int i = 0; i < 6; ++i) {
            std::string line_buffer(40, '.');
            strncpy((char *) line_buffer.data(), m_screen_buffer[i], 40);
            printf("%s\n", line_buffer.c_str());
        }
    }
};

#endif //INC_2022_10_CRT_HPP
