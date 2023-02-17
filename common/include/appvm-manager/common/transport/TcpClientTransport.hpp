#pragma once

#include <appvm-manager/common/helpers/CommonTypes.hpp>
#include <appvm-manager/common/transport/ITransport.hpp>

#include <boost/asio.hpp>

namespace appvm_manager::common
{

class TcpClientTransport final : public IClientTransport
{
public:
    explicit TcpClientTransport(Url url);

    void disconnect() override;
    void sendMessage(IProtocol::IMessage::Ptr message) override;

    OnMessageSignal onMessage() const noexcept override;
    OnErrorSignal onError() const noexcept override;

    void connect() override;

private:
    void onConnectHandler(const boost::system::error_code& errorCode);
    void onReceiveHandler(const boost::system::error_code& errorCode);
    void doClose();

    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::endpoint m_endpoint;
    boost::asio::ip::tcp::socket m_socket;
    IProtocol::IMessage::ByteArray m_buffer;
};

}
