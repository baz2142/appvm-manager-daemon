#include <appvm-manager/common/helpers/CommonTypes.hpp>

#include <boost/format.hpp>

#include <string>

namespace appvm_manager::common
{

Url::Url(std::string netAddress, uint16_t netPort)
    :	host(std::move(netAddress)),
        port(netPort)
{ }


bool Url::operator<(const Url& other) const noexcept
{
    if (host == other.host)
        return port < other.port;

    return host < other.host;
}


std::string Url::toString() const noexcept
{
//    try
    return (boost::format("%1%:%2%") % host % port).str();
//    catch (const std::exception& ex)
//    {
//        logEvent(LogLevel::Warning, "Url::toString: error");
//        return {};
//    }
}

}
