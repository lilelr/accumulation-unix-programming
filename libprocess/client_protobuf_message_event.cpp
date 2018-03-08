
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
#include <stout/ip.hpp>

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
using namespace net;

class ClientProtoProcess : public ProtobufProcess<ClientProtoProcess> {
public:
    ClientProtoProcess(const UPID &server) : server(server) {}


    void initialize() override {


        install<Person>(
                &ClientProtoProcess::receive_person
        );


        Person p;
        p.set_id("12211104");
        p.set_name("lilele");
        send(server, p);
        cout << "send" << endl;
        send(server, p);
        send(server, p);
        send(server, p);
        send(server, p);
        send(server, p);
        send(server, p);

    }

    void receive_person(const UPID &server, Person&& reply_p) {
        cout<<"receive_person"<<endl;
        cout<<server.id<<endl;
        cout<<server.address<<endl;
        cout<<reply_p.id()<<endl;
        cout<<reply_p.name()<<endl;
    }

//    void consume(MessageEvent &&event) override {
//        if (event.message.from == server &&
//            event.message.name == "pong") {
//            cout << "client received pong, ended" << endl;
//            terminate(self());
//        }
//    }

    void send_a_msg() {
        send(server, "we");
    }

    UPID server;
};


int main(int argc, char **argv) {
//PID<ProtoServerProcess> server = spawn(new ProtoServerProcess(), true);
    Try<IP> try_serverIP = IP::parse("10.211.55.4");
    auto serverIP = try_serverIP.get();
    UPID server("(1)",serverIP,40057);
    PID<ClientProtoProcess> client = spawn(new ClientProtoProcess(server), true);
    wait(client);


    return 0;
}