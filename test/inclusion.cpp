/**
    @file
    @author  Alexander Sherikov

    @brief
*/

#include <cpput/all.h>
#include <gtest/gtest.h>


TEST(Inclusion, Inclusion)
{
    EXPECT_TRUE(true);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
