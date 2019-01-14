#include <gtest/gtest.h>

#include <iostream>

#include "bstree.hpp"

class bstreeIntTest : public ::testing::Test
{
protected:
    bstreeIntTest()
        : l0{}, l1{}, l2{}, l3{}, l4{}
    {}
    ~bstreeIntTest() override = default;

    using inode = bstree_node<int>;

    void SetUp() override
    {
        l0 = bstree_create<int>({});
        l1 = bstree_create({1});
        l2 = bstree_create({1, 2});
        l3 = bstree_create({1, 2, 3});
        l4 = bstree_create({1, 2, 3, 4});

        t5 = bstree_create({3, 5, 1, 4, 2, 7, 0});
    }
    void TearDown() override
    {
        bstree_destroy(l0);
        bstree_destroy(l1);
        bstree_destroy(l2);
        bstree_destroy(l3);
        bstree_destroy(l4);

        bstree_destroy(t5);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;

    inode* t5;
};

TEST_F(bstreeIntTest, Depth)
{
    ASSERT_TRUE(bstree_depth(l0) == 0);
    ASSERT_TRUE(bstree_depth(l1) == 1);
    ASSERT_TRUE(bstree_depth(l2) == 2);
    ASSERT_TRUE(bstree_depth(l3) == 3);
    ASSERT_TRUE(bstree_depth(l4) == 4);

    ASSERT_TRUE(bstree_depth(t5) == 3);
}

TEST_F(bstreeIntTest, DepthIter)
{
    ASSERT_TRUE(bstree_depth_iter(l0) == 0);
    ASSERT_TRUE(bstree_depth_iter(l1) == 1);
    ASSERT_TRUE(bstree_depth_iter(l2) == 2);
    ASSERT_TRUE(bstree_depth_iter(l3) == 3);
    ASSERT_TRUE(bstree_depth_iter(l4) == 4);

    ASSERT_TRUE(bstree_depth_iter(t5) == 3);
}

TEST_F(bstreeIntTest, ToString)
{
    ASSERT_TRUE(bstree_to_string(l0) == "");
    ASSERT_TRUE(bstree_to_string(l1) == "1,");
    ASSERT_TRUE(bstree_to_string(l2) == "1,2,");
    ASSERT_TRUE(bstree_to_string(l3) == "1,2,3,");
    ASSERT_TRUE(bstree_to_string(l4) == "1,2,3,4,");

    ASSERT_TRUE(bstree_to_string(t5) == "3,1,0,2,5,4,7,");
}

