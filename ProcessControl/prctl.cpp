#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/prctl.h>
#include <unistd.h>
#include <bits/signum.h>
using namespace std;

int main(int argc, char *argv[]) {

    char *your_process_new_name = "you_process_new_name";
    (void)strcpy(argv[0], your_process_new_name);
    prctl(PR_SET_NAME,  your_process_new_name);
    cout << "Hello, World!" << endl;

    int pid;
    pid = fork();

    if (pid == 0){
        cout<<"child process"<<endl;
        prctl( PR_SET_PDEATHSIG, 9);  //如果父进程退出，将发KILL信号给子进程
        while (true){

        }
        cout<<"child process exit"<<endl;

    }

    return 0;
}