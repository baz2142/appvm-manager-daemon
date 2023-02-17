#include <appvm-manager/common/transport/TcpClientTransport.hpp>

using namespace boost;

namespace appvm_manager::common
{

namespace
{

constexpr size_t BufferSize = 1024 * 1024;

}

TcpClientTransport::TcpClientTransport(Url url)
    :   m_buffer(BufferSize)
{

}


void TcpClientTransport::disconnect()
{
    m_ioService.post(boost::bind(&TcpClientTransport::doClose, this));
}


void TcpClientTransport::sendMessage(IProtocol::IMessage::Ptr message)
{
    const auto data = message->GetData();
    system::error_code error;

    asio::write(m_socket, asio::buffer(data), error);

    if (error)
    {

    }
    else
    {

    }
}


ITransport::OnMessageSignal TcpClientTransport::onMessage() const noexcept
{

}


ITransport::OnErrorSignal TcpClientTransport::onError() const noexcept
{

}


void TcpClientTransport::connect()
{
    m_socket.async_connect(m_endpoint,
        boost::bind(&TcpClientTransport::onConnectHandler, this, boost::asio::placeholders::error));
}


void TcpClientTransport::onConnectHandler(const boost::system::error_code& errorCode)
{
    if (errorCode)
    {
        doClose();
        m_socket.async_connect(
            m_endpoint,
            boost::bind(&TcpClientTransport::onConnectHandler, this, boost::asio::placeholders::error));
    }

    m_socket.async_receive(
        boost::asio::buffer(m_buffer.data(), BufferSize),
        boost::bind(&TcpClientTransport::onReceiveHandler, this, boost::asio::placeholders::error));
}


void TcpClientTransport::onReceiveHandler(const boost::system::error_code& errorCode)
{
    if (errorCode)
    {
        doClose();
        return;
    }

    m_socket.async_receive(boost::asio::buffer(m_buffer.data(), BufferSize),
        boost::bind(&TcpClientTransport::onReceiveHandler, this, boost::asio::placeholders::error));
}


void TcpClientTransport::doClose()
{
    m_socket.close();
}

}
