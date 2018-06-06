//
// Created by lilelr on 6/6/18.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fpin;
    FILE *fpout;
    char buf[1024];

    memset(buf, '\0', sizeof(buf));//初始化buf,以免后面写如乱码到文件中
//    fpin = popen("ls -l", "r"); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    fpin = popen(
            "tar -czf abc.gz /home/lilelr/CLionProjects/acumulation/chapter15inerprocess_communication/popen_start.cpp",
            "r"); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    fpout = fopen("test_popen.txt", "w+"); //新建一个可写的文件

    fread(buf, sizeof(char), sizeof(buf), fpin);  //将刚刚FILE* fpin的数据流读取到buf中
    fwrite(buf, 1, sizeof(buf), fpout);//将buf中的数据写到FILE* fpout对应的流中，也是写到文件中

    pclose(fpin);
    fclose(fpout);

    return 0;
}