
#include <algorithm>
#include <exception>
#include <version.h>

#include "ip_filter.h"

using namespace std;

int main (int argc, char ** argv)
{
    if (argc == 2 && string(argv[1]) == "--version")
    {
        cout<<"ip_filter, version: "<<version()<<endl;
        return 0;
    }
    try
    {
        vector<IpUnit> ipUnits = ParseIpUnits (cin);

        sort (begin (ipUnits), end (ipUnits), [] (const auto &a, const auto &b) { return b < a; });
        //copy (begin(ipUnits), end(ipUnits), ostream_iterator<IpUnit> (cout, " ") );  не компилируется :( ???

        FilterIpUnits (ipUnits,
                       [] (const IpUnit &) { return true; },
                       [] (const IpUnit &ip) { cout << ip << "\n"; }
        );

        FilterIpUnits (ipUnits,
                       [] (const IpUnit &ip) { return ip[0] == 1; },
                       [] (const IpUnit &ip) { cout << ip << "\n"; }
        );

        FilterIpUnits (ipUnits,
                       [] (const IpUnit &ip) { return ip[0] == 46 && ip[1] == 70 ; },
                       [] (const IpUnit &ip) { cout << ip << "\n"; }
        );

        FilterIpUnits (ipUnits,
                       [] (const IpUnit &ip) { return ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46; },
                       [] (const IpUnit &ip) { cout << ip << "\n"; }
        );
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what () << endl;
    }
    catch (...)
    {
        std::cerr << "Undefined exception" << endl;
    }

    return 0;
}
