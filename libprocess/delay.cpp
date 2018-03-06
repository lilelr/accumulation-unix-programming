#include <chrono>
#include <iostream>
#include <thread>
//#include <>
#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/check.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>


using process::MessageEvent;
using process::PID;
using process::UPID;
using process::Process;
using process::spawn;
using process::terminate;
using process::wait;
using process::Clock;
using process::Future;
using process::Promise;


using namespace::std;



class DelayedProcess : public Process<DelayedProcess>
{
public:
    void action(const string& name)
    {
        LOG(INFO) << "hello, " << name;

        promise.set(Nothing());
    }

    Promise<Nothing> promise;
};


int main()
{
//    DelayedProcess process;
//
//    spawn(process);
//
//    LOG(INFO) << "Starting to wait";
//
//    delay(Seconds(5), process.self(), &DelayedProcess::action, "Neil");
//    process.promise.future();
//
//    sleep(5);
//
//    LOG(INFO) << "Done waiting";
//
//
//    terminate(process);
//    wait(process);
//
//    return 0;


    DelayedProcess process;

    spawn(process);

    LOG(INFO) << "Starting to wait";

    Clock::pause();

    delay(Seconds(5), process.self(), &DelayedProcess::action, "Neil");
    process.promise.future();
  Clock::advance(Seconds(6));
//    sleep(5);


    LOG(INFO) << "Done waiting";

    terminate(process);
    wait(process);

    Clock::resume();

    return 0;
}
