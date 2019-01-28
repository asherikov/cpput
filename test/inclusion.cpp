/**
    @file
    @author  Alexander Sherikov

    @brief
*/

#include <cpput/config.h>
#include <cpput/all.h>
#include <gtest/gtest.h>


TEST(Inclusion, Inclusion)
{
    cpput::print_backtrace();
    EXPECT_TRUE(true);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
