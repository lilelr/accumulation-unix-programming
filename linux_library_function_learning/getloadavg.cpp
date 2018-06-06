//
// Created by lilelr on 6/6/18.
//

#include <cstdlib>
#include <iostream>
#include <linux/version.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

using namespace std;

struct Load {
    double one;
    double five;
    double fifteen;
};
// The structure returned by uname describing the currently running system.
struct UTSInfo {
    std::string sysname;    // Operating system name (e.g. Linux).
    std::string nodename;   // Network name of this machine.
    std::string release;    // Release level of the operating system.
    std::string version;    // Version level of the operating system.
    std::string machine;    // Machine hardware platform.
};

int main() {
    double loadArray[3];
    if (getloadavg(loadArray, 3) == -1) {
        cout << "error getloadavg" << endl;
    } else {
        Load load;
        load.one = loadArray[0];
        load.five = loadArray[1];
        load.fifteen = loadArray[2];
        cout << load.one << endl;
        cout << load.five << endl;
        cout << load.fifteen << endl;
    }

    struct utsname sys_name;
    if (uname(&sys_name) < 0) {
        cout << "error uname" << endl;
    }
    cout << sys_name.sysname << endl;
    cout << sys_name.nodename << endl;
    cout << sys_name.release << endl;
    cout << sys_name.version << endl;
    cout << sys_name.machine << endl;
    return 0;
}