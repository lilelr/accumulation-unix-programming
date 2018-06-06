//
// Created by lilelr on 6/6/18.
//
#include <sys/stat.h>

#include <string>


struct Permissions {
    explicit Permissions(mode_t mode) {
        owner.r = (mode & S_IRUSR) != 0;
        owner.w = (mode & S_IWUSR) != 0;
        owner.x = (mode & S_IXUSR) != 0;
        owner.rwx = (mode & S_IRWXU) != 0;
        group.r = (mode & S_IRGRP) != 0;
        group.w = (mode & S_IWGRP) != 0;
        group.x = (mode & S_IXGRP) != 0;
        group.rwx = (mode & S_IRWXG) != 0;
        others.r = (mode & S_IROTH) != 0;
        others.w = (mode & S_IWOTH) != 0;
        others.x = (mode & S_IXOTH) != 0;
        others.rwx = (mode & S_IRWXO) != 0;
        setuid = (mode & S_ISUID) != 0;
        setgid = (mode & S_ISGID) != 0;
        sticky = (mode & S_ISVTX) != 0;
    }

    struct {
        bool r;
        bool w;
        bool x;
        bool rwx;
    } owner, group, others;

    bool setuid;
    bool setgid;
    bool sticky;
};

Permissions permissions(const std::string &path) {
    struct stat status;
    if (stat(path.c_str(), &status) < 0) {
        return nullptr;
    }
    return Permissions(status.st_mode);
}