
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

class ServerProtoProcess : public ProtobufProcess<ServerProtoProcess> {
public:
    void initialize() override {
        install<Person>(
                &ServerProtoProcess::transfer_person
                );

//        install<Person>(
//                &ProtoServerProcess::person_id,
//                 &Person::id
//
//        );
    }


    void transfer_person(const  UPID& from, Person&& p) {
        cout<<from.id<<endl;
        cout << p.id() << endl;
        cout<<p.name()<<endl;
        cout<<"transfer_person"<<endl;
        Person reply_p;
        Resume *reply_p_resume_1 = reply_p.add_my_resume();
        reply_p_resume_1->set_age(25);
        reply_p_resume_1->set_is_man(true);
        reply_p_resume_1->set_sign_id(-577677);

        Resume *reply_p_resume_2 = reply_p.add_my_resume();
        reply_p_resume_2->set_age(23);
        reply_p_resume_2->set_is_man(true);
        reply_p_resume_2->set_sign_id(333);


        PhoneNumber *p_phone_number = reply_p.mutable_phones();
        p_phone_number->set_number("8321585");

        reply_p.set_phone_type(Person::HOME);
//        reply_p.
//        reply_p.set_allocated_phones(&p_phone_number);

        reply_p.set_name("woman");
        reply_p.set_id("f456");
        reply(reply_p);

    }

    void person_id( const  UPID& from,const string&  id) {
        cout<<id<<endl;
       cout <<"person_id"<< endl;

    }

//protected:
//    void consume(MessageEvent &&event) override {
//        if (event.message.name == "ping") {
//            cout << "server received" << endl;
//            send(event.message.from, "pong");
//        }
//        terminate(self());
//    }

};

int main(int argc, char **argv) {
//    PID<ProtoServerProcess> server = spawn(new ProtoServerProcess(), true);
//    PID<ClientProtoProcess> client = spawn(new ClientProtoProcess(server), true);
//    cout << server.address << endl;
//
//    wait(server);
//    wait(client);

    PID<ServerProtoProcess> server = spawn(new ServerProtoProcess(), true);
    cout << server.address << endl;
    cout<<server.id<<endl;
    wait(server);



    return 0;
}