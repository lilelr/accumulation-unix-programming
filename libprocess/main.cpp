/*
 *  simpleprocess.cpp
 *
 *  Created on: Jun 26, 2015
 *  Author: Marco Massenzio
 */

#include <iostream>

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
using std::string;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::MessageEvent;
using process::PID;
using process::UPID;
using process::Process;
using process::spawn;
using process::terminate;
using process::wait;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

using tutorial::Person;



class SimpleProcess : public ProtobufProcess<SimpleProcess> {
public:
    void initialize() {

//        install<string>(
//
//                &SimpleProcess::launchTasks,
//
//                string);
//
//    }




    void launchTasks(const int id) {

        cout<<id<<endl;

    }
    Future<Nothing> doSomething(Person person) {
        std::cout << "Person message: " << person.id() << std::endl;
        return Nothing();
    }

    Future<int> calc(int lhs, int rhs) {
        return Promise<int>(lhs + rhs).future();
    }

private:
    Promise<bool> shouldQuit;
};

class ClientProcess: public ProtobufProcess<ClientProcess>{
public:
    ClientProcess(const UPID& server) : server(server) {}
    void initialize() override
    {
        send(server, "ping");
    }

private:
    UPID server;
        
};

int main() {
    SimpleProcess simpleProcess;
    ClientProcess clientProcess;
    process::PID<SimpleProcess> pid = process::spawn(simpleProcess);
    process::PID<ClientProcess> client_pid = process::spawn(clientProcess);
    cout << "Running simple process" << endl;

    cout << "Dispatching..." << endl;
    Person p;
    double my_id = 12;
    p.set_id(my_id);
    p.set_name("lele");
    process::dispatch(
            pid, &SimpleProcess::doSomething, p);
//
//    Future<int> sum = process::dispatch(pid, &SimpleProcess::calc, 99, 101);
//    sum.then([](int n) {
//        cout << "99 + 101 = " << n << endl;
//        return Nothing();
//    });
//
//    sum.await();
    process::terminate(simpleProcess);
    process::wait(simpleProcess);
    cout << "Done" << endl;

    return EXIT_SUCCESS;
}