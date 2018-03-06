//
// Created by lilelr on 3/6/18.
//

#include <chrono>
#include <iostream>
#include <thread>

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/check.hpp>


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


using process::Process;
using process::spawn;
using process::terminate;
using process::wait;
using process::PID;



struct Person{
    std::string name;
    std::string mother;
    std::string father;
};
struct Person xiao_ming;

Future<Person> find(const std::string& name){
    if(name=="liangmia"){
        Person a;
        a.name="liangmian";
        a.mother="liuli";
        a.father="waigong";
        return a;
    }

    if(name=="lilele"){
        Person lele;
        lele.name="lilele";
        lele.mother="liangmian";
        lele.father="liwen";
        return lele;
    }


    if(name=="liwen"){
        Person liwen;
        liwen.name="liwen";
        liwen.mother="huang";
        liwen.father="li";
        return liwen;
    }



}


// Returns the mother (an instance of `Person`) of the specified `name`.
Future<Person> mother(const std::string& name)
{
    return find(name)
            .then([](const Person& person) {
                return find(person.mother);
            });
}

// Returns a parent (an instance of `Person`) of the specified `name`.
Future<Person> parent(const std::string& name)
{
    return find(name)
            .then([](const Person& person) {
                // Try to find the mother and if that fails try the father!
                return find(person.mother)
                        .recover([=](const Future<Person>&) {
                            return find(person.father);
                        });
            });
}


class FooProcess : public Process<FooProcess> {};

int main(int argc, char** argv)
{
//    Promise<int> promise;
//
//    Future<int> future = promise.future();
//
//    // You can copy a future.
//    Future<int> future2 = future;
//
//    // You can also assign a future (NOTE: this future will never
//    // complete because the Promise goes out of scope, but the
//    // Future is still valid and can be used normally.)
//    future = Promise<int>().future();

//    Promise<int> promise;
//
//    Future<int> future = promise.future();
//
//    CHECK_PENDING(future);
//
//    future.discard();
//
//    CHECK(promise.future().hasDiscard());
//
//    CHECK_PENDING(future); // THE FUTURE IS STILL PENDING!


//    Promise<int>* promise = new Promise<int>();
//
//    Future<int> future = promise->future();
//
//    CHECK(!future.isAbandoned());
//
//    delete promise; // ABANDONMENT!
//
//    CHECK_ABANDONED(future);
//
//    CHECK_PENDING(future); // ALSO STILL PENDING!


    /////////////////////////////////////
//    Promise<int> promise;
//
//    Future<std::string> future = promise.future()
//            .then([](int i) {
//                return stringify(i);
//            });
//
////    future.discard();
//
//    CHECK_PENDING(future);
//
//    promise.set(42);
//    cout<<future.get()<<endl;
//    CHECK_DISCARDED(future); // EVEN THOUGH THE PROMISE COMPLETED SUCCESSFULLY!
    ////////////////////////////////////////////


    //////////////////////////////////////////////////
//    Future<Person> my_mother=mother("lilele");
//    cout<<my_mother.get().name<<endl;

//    Future<Person> my_parent=parent("lilele");
//    cout<<my_parent.get().name<<endl;
    /////////////////////////////////////////////////

    ///////////////
//    FooProcess process;
//    spawn(process);
// terminate(process);
//wait(process);
    /////////////////////////

    ///////
    FooProcess process;
    spawn(process);

    PID<FooProcess> pid = process.self();
    cout<<pid.id<<endl;
    cout<<pid.address<<endl;
   terminate(process);
   wait(process);
    ////////
    return 0;

}

