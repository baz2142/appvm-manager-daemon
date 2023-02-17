#pragma once

#include <appvm-manager/common/helpers/Signals.hpp>

#include "Client.hpp"

namespace appvm_manager::server
{

    struct IListener
    {
        using Ptr = std::shared_ptr<IListener>;
        using OnClientSignal = common::Signal<void(const Client::Ptr&)>;
        using OnErrorSignal = common::Signal<void(const std::string& error)>;

        virtual ~IListener() = default;

        virtual OnClientSignal& onClient() = 0;
        virtual OnErrorSignal& onError() = 0;
    };

}
