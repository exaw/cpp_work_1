
#include "ip_filter.h"

#include <cassert>
#include <charconv>
#include <exception>
#include <iterator>

using namespace std;

optional<IpUnit> TextToIpUnit (const string& text)
{
    size_t p1 = text.find ('\t');
    if (p1 == string::npos)
        return {};

    IpUnit ip;
    const char *start = text.data ();
    const char *stop = text.data () + p1;

    for (int i : {0, 1, 2, 3})
    {
        int value{};
        from_chars_result r = from_chars (start, stop, value);
        if (r.ec != errc{} || value < 0 || value > 255)
            return {};
        ip[i] = value;
        assert(*r.ptr == '.' || *r.ptr == ' ' || *r.ptr == '\t');
        start = r.ptr + 1;
    }

    return ip;
}

vector<IpUnit> ParseIpUnits (std::istream& input)
{
    vector<IpUnit> ipUnits;
    for (string line; getline (input, line);)
    {
        if (line == "")
            break;

        auto optIp = TextToIpUnit (line);
        if (optIp)
        {
            ipUnits.push_back (*optIp);
        }
        else
        {
            throw logic_error ("bad input ip set");
        }
    }

    return ipUnits;
}

ostream &operator<< (ostream& out, const IpUnit& ipUnit)
{
    out << (int) ipUnit[0] << "." << (int) ipUnit[1] << "." << (int) ipUnit[2] << "."
        << (int) ipUnit[3];
    return out;
}
