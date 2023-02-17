#include "Listener.hpp"

namespace appvm_manager::server
{

Listener::Listener()
{

}

IListener::OnClientSignal& appvm_manager::server::Listener::onClient()
{
}

IListener::OnErrorSignal& appvm_manager::server::Listener::onError()
{
}

}

