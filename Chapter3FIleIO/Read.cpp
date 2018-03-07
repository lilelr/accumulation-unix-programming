//
// Created by lilelr on 2/18/18.
//
#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <sys/prctl.h>
#include <unistd.h>
#include <bits/signum.h>
using namespace std;
int main(int argc, char *argv[]) {
    int fd;
    int output_fd;
    void* buf[512];
    int nread_num;
    int read_times =0;
    if((fd=open("/home/lilelr/CLionProjects/acumulation/cmake-build-debug/HappyNewYear",O_RDONLY)) >= 0){

        output_fd = open("/home/lilelr/CLionProjects/acumulation/Chapter3FIleIO/happy_new_year",O_WRONLY|O_CREAT|O_APPEND,777);
        while (true){
            nread_num = read(fd,buf,512);
            read_times++;
            if(nread_num!=0){
                write(output_fd,buf,nread_num);
                if(nread_num!=512){
                    break;
                }
            }
        }
        close(fd);
        close(output_fd);
    }
    printf("%d",read_times);
    return 0;
}