
#include <sstream>

#include <gtest/gtest.h>

#include "ip_filter.h"

using namespace std;

TEST(test_ip_parse, test_positive)
{
    string text =
            "113.162.145.156\t111\t0\n"
            "157.39.22.224\t5\t6\n"
            "0.0.0.0\t5\t6\n"
            "255.255.255.255\t5\t6\n";
    istringstream input (text);

    auto ipUnits = ParseIpUnits (input);
    ASSERT_EQ(ipUnits.size (), 4);

    {
        ASSERT_EQ(ipUnits[0], IpUnit ({113, 162, 145, 156}));
        ASSERT_EQ(ipUnits[1], IpUnit ({157, 39, 22, 224}));
        ASSERT_EQ(ipUnits[2], IpUnit ({0, 0, 0, 0}));
        ASSERT_EQ(ipUnits[3], IpUnit ({255, 255, 255, 255}));
    }
}

TEST(test_ip_parse, test_negative)
{
    for (string s : {
            "113.162.145.abc\t111\t0",
            "113.162.145.123  sdf asf  ff",
            "256.162.145.156\t111\t0",
            "44.162.-45.156\t111\t0",
            "\t",
            ""
    })
    {
        auto optIp = TextToIpUnit (s);
        ASSERT_EQ(optIp, optional<IpUnit>{});
    }
}

TEST(test_ip_out, test_1)
{
    IpUnit ip{1, 12, 255, 0};
    ostringstream out;
    out << ip;
    auto s = out.str ();
    ASSERT_EQ(s, "1.12.255.0");
}

TEST(test_ip_filter, test_1)
{
    vector<IpUnit> ipUnits{
            {1,   12,  255, 0},
            {2,   3,   4,   5},
            {100, 10,  15,  16},
            {255, 255, 255, 255}
    };

    vector<IpUnit> filtered;
    FilterIpUnits (ipUnits,
                   [] (const IpUnit &ip) { return ip[0] + ip[1] + ip[2] + ip[3] == 14; },
                   [&filtered] (const IpUnit &ip) mutable { filtered.push_back (ip); }
    );

    ASSERT_EQ(filtered.size (), 1);
    ASSERT_EQ(filtered[0], ipUnits[1]);

}

int main ()
{
    testing::InitGoogleTest ();
    return RUN_ALL_TESTS ();
}
