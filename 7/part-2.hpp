//
// Created by zhongyang on 2022/12/8.
//

#ifndef INC_2022_PART_2_HPP
#define INC_2022_PART_2_HPP

#include "part-1.hpp"

class Part2 : public Part1
{
public:
    void PrintResult() const override
    {
        constexpr size_t total_size   = 70000000;
        constexpr size_t minimum_size = 30000000;

        size_t used_size     = m_root->GetSize();
        size_t unused_size   = total_size - used_size;
        size_t required_size = minimum_size - unused_size;

        // let's take a walk to find a directory
        // which is the smallest one among those who are larger than required_size

        size_t current_minimum = ~0; // initial with maximum

        m_root->Walk([&](const Node *node)
                     {
                         if (!node->IsDir()) {
                             return;
                         }
                         size_t node_size = node->GetSize();
                         if ((node_size > required_size) && (node_size < current_minimum)) {
                             current_minimum = node_size;
                         }
                     });

        printf("%zu\n", current_minimum);
    }
};

#endif //INC_2022_PART_2_HPP
