
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

class ClientProcess : public Process<ClientProcess>
{
public:
    ClientProcess(const UPID& server) : server(server) {}

    void initialize() override
    {
        send(server, "ping");
    }

    void visit(const MessageEvent& event) {
        if (event.message.from == server &&
            event.message.name == "pong") {
            terminate(self());
        }
    }
    
    UPID server;
};

class ServerProcess : public Process<ServerProcess>
{
public:
protected:
    void visit(const MessageEvent& event)
    {
        if (event.message.name == "ping") {
            send(event.message.from, "pong");
        }
        terminate(self());
    }
};

int main(int argc, char** argv)
{
    PID<ServerProcess> server = spawn(new ServerProcess(), true);
    PID<ClientProcess> client = spawn(new ClientProcess(server), true);
    cout<<server.address<<endl;
    wait(server);
    wait(client);

    return 0;
}