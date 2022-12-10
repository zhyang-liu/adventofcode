//
// Created by zhongyang on 2022/12/7.
//

#ifndef INC_2022_PART_1_HPP
#define INC_2022_PART_1_HPP

#include "instruction.hpp"
#include "cpu.hpp"

#include "../common/utils.h"

#include <list>

class Part1 : public LineProcessor
{
protected:
    cpu_t              m_cpu;
    std::list<int64_t> m_strength;

public:
    Part1()
    {
        m_cpu.RegisterDebugger(std::bind(&Part1::tickCallback, this, std::placeholders::_1));
    }

    int Feed(const std::string &line) override
    {
        auto instruction = instruction_t::Parse(line);
        m_cpu.Execute(instruction);
        return 0;
    }

    void PrintResult() const override
    {
        int64_t   sum = 0;
        for (auto n : m_strength) {
            printf("%lli ", n);
            sum += n;
        }
        printf("\ntotal: %lli\n", sum);
    }

private:
    void tickCallback(const cpu_t &cpu)
    {
        auto cycle = cpu.GetCycle();
        switch (cycle) {
            case 20:
            case 60:
            case 100:
            case 140:
            case 180:
            case 220:
                m_strength.push_back(cycle * cpu.GetRegisterX());
        }
    }
};

#endif //INC_2022_PART_1_HPP
