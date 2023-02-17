#pragma once

#include <appvm-manager/common/transport/ITransport.hpp>

namespace appvm_manager::common
{

class TcpServerTransport final : public IServerTransport
{
public:
    void disconnect() override;
    void sendMessage(IProtocol::IMessage::Ptr message) override;
    OnMessageSignal onMessage() const noexcept override;
    OnErrorSignal onError() const noexcept override;
};


class TcpServerTransportListener final : public IServerTransportListener
{
public:
    OnConnectionSignal OnConnection() const noexcept override;
};

}
