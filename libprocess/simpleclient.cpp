/*
 * simpleserver.cpp
 *
 * Created on: Jun 26, 2015
 * Author: Marco Massenzio, http://codetrips.com
 *
 * This code is explained in a blog entry at the above URL.
 */

#include <chrono>
#include <iostream>
#include <thread>

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>


using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::Response;
using process::http::OK;
using process::http::InternalServerError;
using process::http::URL;


class SimpleProcess : public process::Process<SimpleProcess> {

public:
    SimpleProcess() : ProcessBase("simple") {}

    virtual void initialize();

    Future<bool> done() {
        cout << "are we done yet? " << endl;
        return shouldQuit.future();
    }

    void shutdown() {
        cout << "Shutting down server..." << endl;
        this->shouldQuit.set(true);
    }

private:
    Promise<bool> shouldQuit;
};


void SimpleProcess::initialize() {
    route(
            "/add",
            "Adds the two query arguments",
            [] (Request request) {
                int a = numify<int>(request.url.query["a"]).get();
                int b = numify<int>(request.url.query["b"]).get();

//                cout<<request.body<<endl;
//                cout<<request.url<<endl;
                std::ostringstream result;
                result << "{ \"result\": " << a+b <<"}";
                JSON::Value body = JSON::parse(result.str()).get();
                return OK(body);
            });
    route(
            "/quit",
            "Shuts the server down",
            [this] (Request request) {
                this->shutdown();
                return OK("Shutting down server");
            });
    route(
            "/error",
            "Forces an Internal Server Error (500)",
            [this](Request request) {
                this->shouldQuit.set(false);
                return InternalServerError("We encountered an error");
            });
}


int main() {
    URL url = URL("http", "ubuntu", 39874, "/simple/add?a=33&amp;b=9876");

    Future<Response> future = get(url);
    cout<<future.get().body<<endl;
//    Future<Response> copy_future = future;
    return 0;
}
