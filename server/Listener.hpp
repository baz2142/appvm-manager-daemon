#pragma once

#include "IListener.hpp"

namespace appvm_manager::server
{

class Listener final : public IListener
{
public:
    Listener();

    // IListener interface
public:
    OnClientSignal& onClient() override;
    OnErrorSignal& onError() override;
};

}
