#pragma once

#include <boost/signals2.hpp>

namespace appvm_manager::common
{

template<class Args>
using Signal = boost::signals2::signal<void(Args)>;

}
