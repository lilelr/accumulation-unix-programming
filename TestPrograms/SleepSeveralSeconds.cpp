//
// Created by lilelr on 2/18/18.
//
#include <iostream>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <sys/prctl.h>
#include <unistd.h>
#include <bits/signum.h>
using namespace std;
int main(int argc, char *argv[]) {
    cout<<"sleep 20 seconds starts"<<endl;
    sleep(20);
    cout<<"sleep 20 seconds overs"<<endl;
    return 0;
}
