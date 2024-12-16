using namespace jule;

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool exec(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> args;
    std::string arg;

    while (iss >> arg) {
        args.push_back(arg);
    }

    std::vector<char*> c_args;
    for (auto& a : args) {
        c_args.push_back(const_cast<char*>(a.c_str()));
    }
    c_args.push_back(nullptr); // execvp expects a null-terminated array

    pid_t pid = fork();

    if (pid == 0) {
        execvp(c_args[0], c_args.data());
        return false;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return true;
        }
    } else {
        std::cerr << "fork failed" << std::endl;
    }

    return false;
}
