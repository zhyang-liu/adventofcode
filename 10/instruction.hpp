//
// Created by zhongyang on 2022/12/10.
//

#ifndef INC_2022_10_INSTRUCTION_HPP
#define INC_2022_10_INSTRUCTION_HPP

#include "../common/utils.h"

#include <string>
#include <cstdint>

class instruction_t
{
public:
    enum class command_e : uint64_t
    {
        invalid = 0,
        noop    = 1,
        addx    = 2,
    };

    command_e m_command = command_e::noop;
    int64_t   m_opts    = 0;
    size_t    m_cycles  = 0;

    static instruction_t Parse(const std::string &line)
    {
        int64_t opts;
        size_t  cycles;

        if (HasPrefix(line, "addx")) {
            opts   = ParseInt64(line.substr(5));
            cycles = 2; // addx V takes two cycles to complete;
            return {command_e::addx, opts, cycles};
        } else if (HasPrefix(line, "noop")) {
            cycles = 1;//noop takes one cycle to complete
            return {command_e::noop, 0, cycles};
        } else {
            return {command_e::invalid, 0, 0};
        }
    }

protected:
    instruction_t(command_e command, int64_t opts, size_t cycles)
            : m_command(command), m_opts(opts), m_cycles(cycles) {}
};

#endif //INC_2022_10_INSTRUCTION_HPP
