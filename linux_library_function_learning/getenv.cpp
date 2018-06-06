//
// Created by lilelr on 6/6/18.
//

#include <cstdlib>
#include <iostream>
#include <linux/version.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <signal.h>
#include <error.h>


inline bool exists(const std::string &path) {
    struct stat s;
    if (lstat(path.c_str(), &s) < 0) {
        return false;
    }
    return true;
}

inline bool exists(pid_t pid) {
    // The special signal 0 is used to check if the process exists; see kill(2).
    // If the current user does not have permission to signal pid, but it does
    // exist, then ::kill will return -1 and set errno == EPERM.
    if (kill(pid, 0) == 0 || errno == EPERM) {
        return true;
    }
    return false;
}

int main() {
    char *value = getenv("PATH");
    if (value == nullptr) {
        std::cout << "error" << std::endl;
    } else {
        std::cout << std::string(value) << std::endl;
    }
}