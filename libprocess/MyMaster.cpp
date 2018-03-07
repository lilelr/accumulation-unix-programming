/*
 * simpleserver.cpp
 *
 * Created on: Jun 26, 2015
 * Author: Marco Massenzio, http://codetrips.com
 *
 * This code is explained in a blog entry at the above URL.
 */

#include <chrono>
#include <iostream>
#include <thread>

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>

#include "addressbook.pb.h"


using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

using tutorial::Person;



class MyMaster : public ProtobufProcess<MyMaster> {
public:
    MyMaster() : ProcessBase("simple") {}


    void initialize() {

        install<Person>(

                &MyMaster::launchTasks,

                &Person::id);

    }




    void launchTasks(const int id) {

       cout<<id<<endl;

    }

};




int main() {

}
