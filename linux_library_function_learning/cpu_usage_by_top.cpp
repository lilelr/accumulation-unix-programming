//
// Created by lilelr on 6/7/18.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

struct lele_cpu_usage {
    std::string us;
    std::string sy;
    std::string ni;
    std::string id;
    std::string wa;
};

void get_cpu_usage_by_top(lele_cpu_usage *p_cpu_usage) {
    FILE *fpin;
    char buf[1024];

//    fpin = popen("ls -l", "r"); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    if ((fpin = popen("export TERM=dumb; top", "r")) == nullptr) {
        std::cout << "error top" << std::endl;
    }//将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
//
//    while(fgets(buf,sizeof(buf),fpin)){
//        printf("%s", buf);
//        memset(buf,'\0',sizeof(buf));
//    }
    for (int i = 0; i < 3; i++) {
        memset(buf, '\0', sizeof(buf));//初始化buf,以免后面写如乱码到文件中
        fgets(buf, sizeof(buf), fpin);
//        printf("%s", buf);
    }
    pclose(fpin);

//    memset(buf,'\0',sizeof(buf));

    std::string cpu_usage(buf);
//    std::cout << cpu_usage;
    int index_us_comma = cpu_usage.find_first_of(",");
    std::string us_cpu = cpu_usage.substr(9, index_us_comma - 9);
//    std::cout << us_cpu << std::endl;

    cpu_usage.erase(0, index_us_comma + 1);

    int index_sy_comma = cpu_usage.find_first_of(",");
    std::string sy_cpu = cpu_usage.substr(0, index_sy_comma);
//    std::cout << sy_cpu << std::endl;

    cpu_usage.erase(0, index_sy_comma + 1);

    int index_ni_comma = cpu_usage.find_first_of(",");
    std::string ni_cpu = cpu_usage.substr(0, index_ni_comma);
//    std::cout << ni_cpu << std::endl;

    cpu_usage.erase(0, index_ni_comma + 1);

    int index_id_comma = cpu_usage.find_first_of(",");
    std::string id_cpu = cpu_usage.substr(0, index_id_comma);
//    std::cout << id_cpu << std::endl;

    cpu_usage.erase(0, index_id_comma + 1);

    int index_wa_comma = cpu_usage.find_first_of(",");
    std::string wa_cpu = cpu_usage.substr(0, index_wa_comma);

    p_cpu_usage->us = us_cpu;
    p_cpu_usage->sy = sy_cpu;
    p_cpu_usage->ni = ni_cpu;
    p_cpu_usage->id = id_cpu;
    p_cpu_usage->wa = wa_cpu;

//    std::cout << wa_cpu << std::endl;


}
int main() {

    lele_cpu_usage cpu_usage;
    get_cpu_usage_by_top(&cpu_usage);
    std::cout << cpu_usage.us << cpu_usage.sy << cpu_usage.id << cpu_usage.ni << cpu_usage.wa << std::endl;
    return 0;
}