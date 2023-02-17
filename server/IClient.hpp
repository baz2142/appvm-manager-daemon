#pragma once

#include <memory>

namespace appvm_manager::server
{

struct IClient
{
using Ptr = std::shared_ptr<IClient>;
};

}
