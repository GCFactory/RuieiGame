
#include "gtest/gtest.h"

using namespace std;

TEST(TestExample, Subtest_1) {
ASSERT_TRUE(1 == 1);
}

//TEST(TestExample, Subtest_2) {
//ASSERT_FALSE('b' == 'b');
//cout << "continue test after failure" << endl;
//}


// Don't touch
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}