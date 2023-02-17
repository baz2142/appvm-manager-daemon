#pragma once

#include <appvm-manager/common/protocol/IProtocol.hpp>

#include "IClient.hpp"
#include "IListener.hpp"

#include <boost/signals2/connection.hpp>

#include <condition_variable>
#include <functional>
#include <memory>
#include <stop_token>
#include <queue>

namespace appvm_manager::server
{

class Server
{
private:
    using Task = std::function<void()>;
    using SignalConnections = std::vector<boost::signals2::scoped_connection>;

    struct ClientInfo
    {
        IClient::Ptr        ptr;
        SignalConnections	connections;

        ClientInfo(const Client::Ptr& client, SignalConnections&& clientConnections)
            :	ptr(client),
                connections(std::move(clientConnections))
        { }
    };

    std::map<std::string, ClientInfo>   m_clients;

    std::condition_variable             m_tasksCondition;
    std::mutex                          m_tasksMutex;
    std::queue<Task>                    m_tasks;

    std::stop_source                    m_stopSource;
    std::stop_token                     m_stopToken;

    IListener::Ptr                      m_listener;
    SignalConnections                   m_connections;

public:
    Server();

    void start(std::stop_token stopToken);

private:
//    bool isStopReqested() noexcept
//    { return m_stopSource.stop_requested() || m_stopToken.stop_requested(); }

    void addTask(const Task& task);

    template<class Signal, class Handler>
    boost::signals2::connection connectAsTask(Signal& signal, const Handler& handler)
    {
        return signal.connect([this, handler](auto&& ...signalParameters)
        { addTask(std::bind(handler, std::forward<decltype(signalParameters)>(signalParameters)...)); });
    }

    void onListenerClientHandler(const Client::Ptr& client);
    void onListenerErrorHandler();

    void onMessageHandler(const std::string& senderName, const common::IProtocol::IMessage::Ptr& message);
    void onClientDisconnectedHandler(const std::string& senderName);
};

}
