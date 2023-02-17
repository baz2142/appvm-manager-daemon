#pragma once

#include <appvm-manager/common/protocol/IProtocol.hpp>

namespace appvm_manager::common
{

class ProtobufProtocol final : public IClientProtocol
{
public:
    ProtobufProtocol() = default;

    [[nodiscard]] IMessage::Ptr makeGetVmListRequest() const noexcept override;
    [[nodiscard]] IMessage::Ptr makeGetVmInfoRequest(VmId id) const noexcept override;
    [[nodiscard]] IMessage::Ptr makeGetVmDependenciesRequest(VmId id) const noexcept override;
    [[nodiscard]] IMessage::Ptr makeStartVmRequest(VmId id) const noexcept override;
    [[nodiscard]] IMessage::Ptr makeStopVmRequest(VmId id) const noexcept override;
    [[nodiscard]] IMessage::Ptr makeVmNotificationResponse() const noexcept override;
};

}
