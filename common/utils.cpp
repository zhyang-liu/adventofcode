//
// Created by zhongyang on 2022/12/3.
//

#include "utils.h"

#include <fstream>
#include <unistd.h>

FileLoader::FileLoader(std::string path) : m_path(std::move(path)) {}

int FileLoader::Process(LineProcessor &processor) {
    if (m_path.empty()) {
        return 1;
    }

    std::ifstream ifs(m_path);
    if (!ifs.is_open()) {
        char cwd[PATH_MAX] = {0};
        getcwd(cwd, PATH_MAX);
        fprintf(stderr, "failed to open: %s, cwd: %s\n", m_path.c_str(), cwd);
        return 2;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        int r = processor.Feed(line);
        if (r != 0) {
            fprintf(stderr, "failed to process line: %s\nreturn: %d\n", line.c_str(), r);
            return r;
        }
    }

    processor.PrintResult();
    return 0;
}
