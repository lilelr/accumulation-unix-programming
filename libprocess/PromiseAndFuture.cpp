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


struct Person{
    std::string name;
    std::string mother;
};
struct Person xiao_ming;

Future<Person> find(const std::string& name){
    if(name=="liangmian"){
        Person a;
        a.name="liangmian";
        a.mother="liuli";
        return a;
    }

    if(name=="lilele"){
        Person lele;
        lele.name="lilele";
        lele.mother="liangmian";
        return lele;
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


    xiao_ming.name="iji";
    //////////////////////////////////////////////////
    Future<Person> my_mother=mother("lilele");
    cout<<my_mother.get().name<<endl;
    /////////////////////////////////////////////////
    return 0;

}

