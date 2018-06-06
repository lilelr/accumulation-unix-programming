//
// Created by YuXiao on 5/6/18.
//
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    pid_t pid;
    int while_count = 20;

    cout << "input the number of while_count,default = 20" << endl;
    cin >> while_count;
    for (int i = 0; i < while_count; i++) {
        if ((pid = fork()) < 0) {
            cout << "error pid" << endl;
        } else if (pid == 0) {
            cout << "child process" << i << endl;
            while (true) {

            }
        }
    }



//    if((pid = fork()) < 0 ){
//        cout<<"error pid"<<endl;
//    }else if(pid ==0){
//        cout<<"child process2"<<endl;
//        while (true){
//
//        }
//        _exit(0);
//
//    }

    cout << "parent" << endl;
    return 0;
}