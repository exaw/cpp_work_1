
#include <gtest/gtest.h>

#include "lib.h"

TEST(test_version_1, test_version)
{
	ASSERT_GT(version(), 0);
}

int main()
{
    //return version() > 0 ? 0 : 1;
    return RUN_ALL_TESTS();
}
