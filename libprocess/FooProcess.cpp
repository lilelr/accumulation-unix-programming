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


using process::MessageEvent;
using process::PID;
using process::UPID;
using process::Process;
using process::spawn;
using process::terminate;
using process::wait;
using namespace::std;


class FooProcess : public Process<FooProcess>
{
public:
    void foo(int i){
        cout<<"lele       "<<i<<endl;
//        LOG(INFO)<<"lele       "<<i<<endl;
    }
};

class Foo
{
public:
    Foo()
    {
        process::spawn(process);
    }

    ~Foo()
    {
        process::terminate(process);
        process::wait(process);
    }

    void foo(int i)
    {
        dispatch(process, &FooProcess::foo, i);
    }

private:
    FooProcess process;
};

int main(int argc, char** argv)
{
    Foo foo;

    foo.foo(42);

    return 0;
}