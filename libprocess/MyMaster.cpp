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


using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;


class MyMaster : public ProtobufProcess<MyMaster> {
public:
    MyMaster() : ProcessBase("simple") {}


    void initialize() {

        install<LaunchTasksMessage>(

                &MyMaster::launchTasks,

                &LaunchTasksMessage::id,

                &LaunchTasksMessage::tasks);

    }




    void launchTasks(const int id,

                     const vector<TaskInfo>& tasks) {

        for (int i = 0; i < tasks.size(); i++) {

//launch tasks[i];

        }

    }

};




int main() {

}
