#ifdef DEBUG_MODE
    #undef BACKWARD_HAS_BFD
    #define BACKWARD_HAS_BFD 1
    #include <backward.hpp>
#endif

//#include <boost/format.hpp>


#include <csignal>
#include <iostream>
#include <memory>

#include <appvm-manager/common/protocol/IProtocol.hpp>

#include "Server.hpp"

using namespace appvm_manager::server;

namespace
{
#ifdef DEBUG_MODE
    backward::SignalHandling sh;
#endif

    std::stop_source stopSource;

    void sigtermHandler([[maybe_unused]] int signum)
    {
        stopSource.request_stop();
    }
}


int main(int argc, char *argv[])
{
//    unsigned port = 8091;

    std::cout << "Enter the server's port: ";

//    std::cin >> port;

    std::signal(SIGTERM, sigtermHandler);
    std::signal(SIGINT, sigtermHandler);

    try
    {
//        initLogger(LogLevel::Debug, "server");
//        setThreadName("main");

        Server server;
        server.start(stopSource.get_token());
    }
    catch (const std::exception& ex)
    { }
//    { logEvent(LogLevel::Error, boost::format("Terminating the application due to an unhandled exception: %1%") % ex.what()); }

//    deinitLogger();

    return 0;
}

