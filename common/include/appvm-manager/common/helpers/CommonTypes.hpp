#pragma once

#include <string>

namespace appvm_manager::common
{

struct Url
{
    std::string	host;
    uint16_t	port;

    Url(std::string netAddress, uint16_t netPort);

    bool operator<(const Url& other) const noexcept;

    [[nodiscard]] std::string toString() const noexcept;
};


}
