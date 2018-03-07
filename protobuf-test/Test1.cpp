//
// Created by lilelr on 3/7/18.
//
#include <iostream>
#include <fstream>
#include <vector>


#include "Test1.pb.h"
using  namespace std;
using namespace tutorial;

int main(){
    Test1 ww;
    ww.set_a(150);
  cout<<ww.a()<<endl;
    {
        // Write the new address book back to disk.
        fstream output("/home/lilelr/CLionProjects/acumulation/protobuf-test/test1", ios::out | ios::trunc | ios::binary);
        if (!ww.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}