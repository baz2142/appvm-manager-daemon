#include <appvm-manager/common/protocol/ProtobufClientProtocol.hpp>

#include <appvm-manager/common/protocol/Protocol.pb.h>

namespace appvm_manager::common
{

namespace
{

class Message final : public IProtocol::IMessage
{
public:
    explicit Message(std::unique_ptr<google::protobuf::Message> message)
        :   m_message(std::move(message))
    { }

    [[nodiscard]] ByteArray GetData() const override
    {
        return {};
    }

private:
    std::unique_ptr<google::protobuf::Message> m_message;
};

template<class T>
IProtocol::IMessage::Ptr makeMessagePtr(T&& protobufMessage)
{
    return std::make_shared<Message>(std::move(protobufMessage));
}

}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeGetVmListRequest() const noexcept
{
    return makeMessagePtr(std::make_unique<protocol::Message_ClientMessage_GetVmListRequest>());
}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeGetVmInfoRequest(VmId id) const noexcept
{
    auto rq = std::make_unique<protocol::Message_ClientMessage_GetVmInfoRequest>();
    rq->set_vm_id(id);

    return makeMessagePtr(rq);
}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeGetVmDependenciesRequest(VmId id) const noexcept
{
    auto rq = std::make_unique<protocol::Message_ClientMessage_GetVmDependenciesRequest>();
    rq->set_vm_id(id);

    return makeMessagePtr(rq);
}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeStartVmRequest(VmId id) const noexcept
{
    auto rq = std::make_unique<protocol::Message_ClientMessage_StartVmRequest>();
    rq->set_vm_id(id);

    return makeMessagePtr(rq);
}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeStopVmRequest(VmId id) const noexcept
{
    auto rq = std::make_unique<protocol::Message_ClientMessage_StopVmRequest>();
    rq->set_vm_id(id);

    return makeMessagePtr(rq);
}

IProtocol::IMessage::Ptr appvm_manager::common::ProtobufProtocol::makeVmNotificationResponse() const noexcept
{
    auto rs = std::make_unique<protocol::Message_ClientMessage_VmNotificationResponse>();

    return makeMessagePtr(rs);
}

}
