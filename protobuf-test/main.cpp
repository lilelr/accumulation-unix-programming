//
// Created by lilelr on 3/7/18.
//
#include <iostream>
#include <fstream>
#include <vector>


#include "addressbook.pb.h"
using  namespace std;
using tutorial::Person;

int main(){
    Person p;
    p.set_name("lilele");
    p.set_id(12211104);
    {
        // Write the new address book back to disk.
        fstream output("/home/lilelr/CLionProjects/acumulation/protobuf-test/addressbook", ios::out | ios::trunc | ios::binary);
        if (!p.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}