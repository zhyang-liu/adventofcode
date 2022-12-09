//
// Created by zhongyang on 2022/12/3.
//

#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <string>

// an interface
class LineProcessor
{
public:
    virtual int Feed(const std::string &line) = 0;

    virtual void PrintResult() const = 0;
};

// the file loader
class FileLoader
{
private:
    std::string m_path;

public:
    explicit FileLoader(std::string path);

    int Process(LineProcessor &processor);
};

inline bool HasPrefix(const std::string &content, const std::string &prefix)
{
    return content.rfind(prefix, 0) == 0;
}

inline std::string TrimPrefixSpaces(const std::string &content)
{
    return content.substr(content.find_first_not_of(" \t\n\r\f\v"));
}

inline std::string TrimPostfixSpaces(const std::string &content)
{
    return content.substr(0, content.find_last_not_of(" \t\n\r\f\v") + 1);
}

inline std::string TrimSpaces(const std::string &content)
{
    return TrimPostfixSpaces(TrimPrefixSpaces(content));
}

inline int64_t ParseInt64(const std::string &content, size_t *bytes_read = nullptr)
{
    char *end   = nullptr;
    auto result = strtoll(content.c_str(), &end, 10);
    if (bytes_read) {
        *bytes_read = end - content.c_str();
    }
    return result;
}

#endif //INC_1_UTILS_H
