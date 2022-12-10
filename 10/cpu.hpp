//
// Created by zhongyang on 2022/12/10.
//

#ifndef INC_2022_10_CPU_HPP
#define INC_2022_10_CPU_HPP

#include <cstdint>
#include <utility>

#include "instruction.hpp"

class cpu_t
{
public:
    typedef std::function<void(const cpu_t &cpu)> tick_callback_t;

protected:
    int64_t         m_x             = 1; // "During the first cycle, X is 1"
    size_t          m_cycle         = 0;
    tick_callback_t m_tick_callback = nullptr;

public:
    void RegisterDebugger(tick_callback_t callback)
    {
        m_tick_callback = std::move(callback);
    }

    void Execute(const instruction_t &instruction)
    {
        for (size_t c = 0; c < instruction.m_cycles; ++c) {
            ++this->m_cycle;
            if (m_tick_callback) {
                m_tick_callback(*this);
            }
        }
        doInstruction(instruction);
    }

    size_t GetCycle() const { return m_cycle; }

    int64_t GetRegisterX() const { return m_x; }

protected:
    void doInstruction(const instruction_t &instruction)
    {
        switch (instruction.m_command) {
            case instruction_t::command_e::invalid:
            case instruction_t::command_e::noop:
                break;
            case instruction_t::command_e::addx:
                m_x += instruction.m_opts;
                break;
        }
    }
};

#endif //INC_2022_10_CPU_HPP
