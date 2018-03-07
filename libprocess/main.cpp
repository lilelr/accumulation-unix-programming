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

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

using tutorial::Person;



class SimpleProcess : public ProtobufProcess<SimpleProcess> {
public:

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


int main() {
    SimpleProcess simpleProcess;
    process::PID<SimpleProcess> pid = process::spawn(simpleProcess);

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