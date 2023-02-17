#pragma once

#include <appvm-manager/common/helpers/Signals.hpp>
#include <appvm-manager/common/protocol/IProtocol.hpp>

namespace appvm_manager::common
{

struct ITransport
{
    using Ptr = std::shared_ptr<ITransport>;
    using OnMessageSignal = Signal<IProtocol::IMessage::Ptr>;
    using OnErrorSignal = Signal<void(std::string_view error)>;

    virtual ~ITransport() = default;

    virtual void disconnect() = 0;
    virtual void sendMessage(IProtocol::IMessage::Ptr message) = 0;

    virtual OnMessageSignal onMessage() const noexcept = 0;
    virtual OnErrorSignal onError() const noexcept = 0;
};


struct IClientTransport : public ITransport
{
    virtual void connect() = 0;
};


struct IServerTransport : public ITransport
{ };


struct IServerTransportListener
{
    using OnConnectionSignal = Signal<void(const IServerTransport::Ptr&)>;

    virtual OnConnectionSignal OnConnection() const noexcept = 0;
};

}
