#include <iostream>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <sys/prctl.h>
#include <unistd.h>
#include <bits/signum.h>
using namespace std;

char* env_init[]={"USER=unknown","PATH=/tmp",NULL};
int main(int argc, char *argv[]) {

    pid_t pid;
    if((pid= fork()) < 0){
        cout<<"fork error"<<endl;
    }else if(pid == 0){
//        if(execle("/home/lilelr/CLionProjects/cumulation/cmake-build-debug/HappyNewYear","HappyNewYear", "myarg1",
//                  "MY ARG2",(char *)0, env_init)<0){
//            cout<<"execle error"<<endl;
//        }
        if(execle("/home/lilelr/CLionProjects/cumulation/cmake-build-debug/sleep_several_seconds","sleep_several_seconds", "myarg1",
                  "MY ARG2",(char *)0, env_init)<0){
            cout<<"execle error"<<endl;
        }
    }

    if(waitpid(pid,NULL,0)<0){
        cout<<"wait error"<<endl;
    }

    cout<<"main process"<<endl;

//    if((pid=vfork()) < 0){
//        cout<<"fork error 2"<<endl;
//    }else if(pid == 0){
//
//        if(execlp("sleep","sleep","100", nullptr)<0){
//            cout<<"execlp error"<<endl;
//        }
//        cout<<"sleep for 10 secs"<<endl;
//
//    }

//    for(int i=0;i<100;i++){
//        cout<<i<<endl;
//    }
//    cout<<"Happy new year!"<<endl;
    exit(0);
}