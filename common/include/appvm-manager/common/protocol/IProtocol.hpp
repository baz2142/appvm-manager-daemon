#pragma once

#include <memory>
#include <vector>

namespace appvm_manager::common
{

struct IProtocol
{
    using Ptr = std::shared_ptr<IProtocol>;
    using VmId = std::string;

    struct IMessage
    {
        using Ptr = std::shared_ptr<IMessage>;
        using ByteArray = std::vector<std::byte>;

        virtual ~IMessage() = default;

        [[nodiscard]] virtual ByteArray GetData() const = 0;
    };

    virtual ~IProtocol() = default;
};


struct IClientProtocol : public IProtocol
{
    [[nodiscard]] virtual IMessage::Ptr makeGetVmListRequest() const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeGetVmInfoRequest(VmId id) const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeGetVmDependenciesRequest(VmId id) const noexcept = 0;

    [[nodiscard]] virtual IMessage::Ptr makeStartVmRequest(VmId id) const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeStopVmRequest(VmId id) const noexcept = 0;

    [[nodiscard]] virtual IMessage::Ptr makeVmNotificationResponse() const noexcept = 0;
};


struct IServerProtocol : public IProtocol
{
    [[nodiscard]] virtual IMessage::Ptr makeGetVmListResponse() const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeGetVmInfoResponse() const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeGetVmDependenciesResponse() const noexcept = 0;

    [[nodiscard]] virtual IMessage::Ptr makeStartVmResponse() const noexcept = 0;
    [[nodiscard]] virtual IMessage::Ptr makeStopVmResponse() const noexcept = 0;

    [[nodiscard]] virtual IMessage::Ptr makeVmNotificationRequest(VmId id, std::string_view notification) const noexcept = 0;
};

}
