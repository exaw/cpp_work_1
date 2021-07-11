#pragma once

#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using IpUnit = std::array<uint8_t, 4>;

std::optional<IpUnit> TextToIpUnit (const std::string &text);

std::vector<IpUnit> ParseIpUnits (std::istream &input);

std::ostream &operator<< (std::ostream &out, const IpUnit &ipUnit);

template<typename Filter, typename Maker>
void FilterIpUnits (const std::vector<IpUnit> &ipUnits, Filter filter, Maker maker)
{
    for ( const auto& ip : ipUnits )
    {
        if ( filter (ip) == true )
            maker(ip);
    }
}



