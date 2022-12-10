//
// Created by zhongyang on 2022/12/10.
//

#ifndef INC_2022_10_PART_2_HPP
#define INC_2022_10_PART_2_HPP

#include "part-1.hpp"
#include "crt.hpp"

// You count the pixels on the CRT: 40 wide and 6 high
// the sprite is 3 pixels wide,
// and the X register sets the horizontal position of the middle of that sprite.
//
// the CRT draws a single pixel during each cycle.
// If the sprite is positioned such that one of its three pixels is the pixel currently being drawn,
// the screen produces a lit pixel (#); otherwise, the screen leaves the pixel dark (.).
class Part2 : public Part1
{
protected:
    crt_t m_crt;

public:
    Part2()
    {
        m_cpu.RegisterDebugger(std::bind(&Part2::tickCallback2, this, std::placeholders::_1));
    }

    void PrintResult() const override
    {
        m_crt.PrintBuffer();
        printf("\n");
    }

protected:
    void tickCallback2(const cpu_t &cpu)
    {
        m_crt.Tick(cpu.GetRegisterX());
    }
};

#endif //INC_2022_10_PART_2_HPP
