#include "Server.hpp"

//#include "common/Logger.hpp"
#include <appvm-manager/common/protocol/IProtocol.hpp>

#include <algorithm>

namespace appvm_manager::server
{

    namespace
    {

        const auto ClientInitTimeout = std::chrono::seconds(30);
        const auto TaskConditionSleepTimeout = std::chrono::minutes(1);

    }

    Server::Server()
//        :	_listener(address)
    {
//        m_connections.emplace_back(connectAsTask(m_listener->onClient(), std::bind(&Server::onListenerClientHandler, this, std::placeholders::_1)));
        m_connections.emplace_back(connectAsTask(m_listener->onError(), std::bind(&Server::onListenerErrorHandler, this)));
    }


    void Server::start(std::stop_token stopToken)
    {
        while (!stopToken.stop_requested())
        {
            {
                std::unique_lock l(m_tasksMutex);
                m_tasksCondition.wait_for(l, TaskConditionSleepTimeout, [this]{ return m_stopSource.request_stop() || !m_tasks.empty(); });
            }

            if (stopToken.stop_requested())
                break;

//            for (auto it = _uninitialisedClients.begin(); it != _uninitialisedClients.end(); )
//            {
//                if (it->second.second + ClientInitTimeout < std::chrono::steady_clock::now())
//                {
//                    logEvent(LogLevel::Debug, boost::format("Server::start: erasing uninitialised client: %1% ") % it->first.toString());
//                    it = _uninitialisedClients.erase(it);
//    Server      }
//                else
//                    ++it;
//            }

            auto localTasks = [this]
            {
                std::lock_guard l(m_tasksMutex);
                return std::exchange(m_tasks, {});
            }();

            while (!localTasks.empty())
            {
                const Task task = localTasks.front();
                localTasks.pop();

                try
                { task(); }
                catch (const std::exception& ex)
                { } // logEvent(LogLevel::Error, boost::format("Server::start: task: %1%") % ex.what()); }
            }
        }
    }

    void Server::addTask(const Task& task)
    {
        std::lock_guard l(m_tasksMutex);
        m_tasks.push(task);
        m_tasksCondition.notify_one();
    }


    void Server::onListenerClientHandler(const Client::Ptr& client)
    {
//        logEvent(LogLevel::Info, boost::format("A new connection from: %1%") % connection->getEndpointAddress().toString());

//        const auto client = std::make_shared<Client>(connection);

//        SignalConnections signalConnections;
//        signalConnections.emplace_back(
//                connectAsTask(client->onInit(), std::bind(&Server::onInitHandler, this, connection->getEndpointAddress(), std::placeholders::_1)));

//        _uninitialisedClients.emplace(
//                connection->getEndpointAddress(),
//                std::make_pair(ClientInfo(client, std::move(signalConnections)), std::chrono::steady_clock::now()));
    }


    void Server::onListenerErrorHandler()
    {
//        logEvent(LogLevel::Error, "Server::onListenerErrorHandler: Error!");
        m_stopSource.request_stop();
        m_tasksCondition.notify_one();
    }


//    void Server::onInitHandler(const Url& clientAddress, const protocol::ClientMessage::Init& message)
//    {
//        auto uninitialisedClientIt = _uninitialisedClients.find(clientAddress);
//        if (uninitialisedClientIt == _uninitialisedClients.end())
//            return;

//        const ClientPtr sender = uninitialisedClientIt->second.first.ptr;
//        _uninitialisedClients.erase(uninitialisedClientIt);

//        logEvent(LogLevel::Debug, boost::format("Init from: %1%") % message.name());

//        const bool nameIsAvailable = _clients.count(message.name()) == 0;

//        if (nameIsAvailable)
//        {
//            SignalConnections connections;
//            connections.emplace_back(connectAsTask(sender->onMessage(), std::bind(&Server::onMessageHandler, this, message.name(), std::placeholders::_1)));
//            connections.emplace_back(connectAsTask(sender->onDisconnected(), std::bind(&Server::onClientDisconnectedHandler, this, message.name())));

//            const auto request = protocol::makeServerRequestNewClient(message.name());

//            try
//            {
//                for (const auto& [_, client] : _clients)
//                    client.ptr->enqueueMessage(request);
//            }
//            catch (const std::exception& ex)
//            { logEvent(LogLevel::Error, boost::format("Server::onInitHandler: %1%") % ex.what()); }

//            _clients.emplace(message.name(), ClientInfo(sender, std::move(connections)));
//        }

//        sender->enqueueMessage(protocol::makeServerRequestInitResult(nameIsAvailable,
//                (nameIsAvailable ? boost::format("Welcome, %1%") % message.name() : boost::format("Name %1% is not available") % message.name()).str()));
//    }


    void Server::onMessageHandler(const std::string& senderName, const common::IProtocol::IMessage::Ptr &message)
    {
//        logEvent(LogLevel::Debug, boost::format("Message from: %1%: %2%") % senderName % message.message());

//        common::IServerSideProtocol::
//        const auto request = protocol::makeServerRequestClientSentMessage(
//                senderName,
//                message.message(),
//                std::chrono::steady_clock::now().time_since_epoch().count());

//        for (const auto& [name, client] : _clients)
//        {
//            if (name != senderName)
//                client.ptr->enqueueMessage(request);
//        }
    }


    void Server::onClientDisconnectedHandler(const std::string& senderName)
    {
//        logEvent(LogLevel::Info, boost::format("Client with name: '%1%' disconnected") % senderName);

//        _clients.erase(senderName);

//        const auto request = protocol::makeServerRequestClientDisconnected(senderName);

//        for (const auto& [_ ,client] : _clients)
//        { client.ptr->enqueueMessage(request); }
    }

}
