#include "gtest/gtest.h"

class CRectTest : public ::testing::Test {
};

//TEST_F(CRectTest, CheckPerimeter)
//{
//    int x = 5;
//    int y = 6;
//    int z = x + y;
////    ASSERT_TRUE(z == 11);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}