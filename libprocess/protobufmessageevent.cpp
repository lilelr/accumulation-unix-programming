
#include <chrono>
#include <iostream>
#include <thread>

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/check.hpp>


#include <process/protobuf.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>

#include "addressbook.pb.h"


using process::MessageEvent;
using process::PID;
using process::UPID;
using process::ProcessBase;
using process::Process;

using process::spawn;
using process::terminate;
using process::wait;
using namespace ::std;
using namespace ::tutorial;

class ClientProtoProcess : public ProtobufProcess<ClientProtoProcess> {
public:
    ClientProtoProcess(const UPID &server) : server(server) {}

    void initialize() override {
        Person p;
        p.set_id("33");
        p.set_name("lilele");
        send(server, p);
        cout << "send" << endl;
    }

    void consume(MessageEvent &&event) override {
        if (event.message.from == server &&
            event.message.name == "pong") {
            cout << "client received pong, ended" << endl;
            terminate(self());
        }
    }

    void send_a_msg(){
        send(server, "we");
    }

    UPID server;
};

class ProtoServerProcess : public ProtobufProcess<ProtoServerProcess> {
public:
    void initialize() override {
        install<Person>(
                &ProtoServerProcess::launchTasks
                );

        install<Person>(
                &ProtoServerProcess::person_id,
                 &Person::id

        );
    }


    void launchTasks(const  UPID& from, Person&& p) {
        cout<<from.id<<endl;
        cout << p.id() << endl;

    }

    void person_id( const  UPID& from,const string&  id) {
        cout<<id<<endl;
//        cout << p.id() << endl;

    }

protected:
    void consume(MessageEvent &&event) override {
        if (event.message.name == "ping") {
            cout << "server received" << endl;
            send(event.message.from, "pong");
        }
        terminate(self());
    }

};

int main(int argc, char **argv) {
    PID<ProtoServerProcess> server = spawn(new ProtoServerProcess(), true);
    PID<ClientProtoProcess> client = spawn(new ClientProtoProcess(server), true);
    cout << server.address << endl;

    wait(server);
    wait(client);

    return 0;
}