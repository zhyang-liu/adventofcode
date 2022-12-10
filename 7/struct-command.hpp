//
// Created by zhongyang on 2022/12/8.
//

#ifndef INC_2022_STRUCT_COMMAND_HPP
#define INC_2022_STRUCT_COMMAND_HPP

#include "../common/utils.h"

#include <string>

class Command
{
public:
    enum class Type : size_t
    {
        None = 0,
        Ls   = 1,
        Cd   = 2,
    };

public:
    static Command ParseCommand(std::string line)
    {
        // assume always starts with "$ ".
        line = line.substr(2);

        if (HasPrefix(line, "cd ")) {
            return {Type::Cd, TrimSpaces(line.substr(3))};
        } else if (HasPrefix(line, "ls")) {
            return {Type::Ls, ""};
        } else {
            return {};
        }
    }

    Command::Type GetType() const
    {
        return m_type;
    }

    const std::string &GetSubject() const
    {
        return m_subject;
    }

    bool IsValid() const
    {
        return m_type != Type::None;
    }

protected:
    Type        m_type = Type::None;
    std::string m_subject;

    Command() = default;

    Command(Type type, std::string subject)
            : m_type(type), m_subject(std::move(subject))
    {
    }
};

#endif //INC_2022_STRUCT_COMMAND_HPP
