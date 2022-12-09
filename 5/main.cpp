#include "part-1.hpp"
#include "part-2.hpp"

int main(int argc, char **argv)
{
    FileLoader l("input");
    size_t     n_stacks = 9;// 9 for input

    if (argc > 1) {
        n_stacks = strtoul(argv[1], nullptr, 10);
    }

    Part2 d(n_stacks);
    return l.Process(d);
}
