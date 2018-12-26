#include <iostream>
#include <cassert>

#include <gtest/gtest.h>

#include "slist.hpp"

class SlistIntTest : public ::testing::Test
{
protected:
    SlistIntTest()
        : l0{}, l1{}, l2{}, l3{}, l4{}
    {}
    ~SlistIntTest() override = default;

    using inode = slist_node<int>;

    void SetUp() override
    {
        l0 = create<int>({});
        l1 = create({1});
        l2 = create({1, 2});
        l3 = create({1, 2, 3});
        l4 = create({1, 2, 3, 4});
    }
    void TearDown() override
    {
        destroy(l0);
        destroy(l1);
        destroy(l2);
        destroy(l3);
        destroy(l4);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;
};

TEST_F(SlistIntTest, Clone)
{
    auto cloned_l4 = clone(l4);
    EXPECT_TRUE(are_equal(l4, cloned_l4));
    EXPECT_FALSE(are_equal(l3, cloned_l4));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

