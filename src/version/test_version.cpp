
#include <iostream>

#include <gtest/gtest.h>

#include "version.h"

TEST(test_version_1, test_version)
{
	ASSERT_GT(version(), 0);
}

int main()
{
    testing::InitGoogleTest ();
    return RUN_ALL_TESTS();
}
