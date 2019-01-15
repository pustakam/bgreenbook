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
        t6 = bstree_create({3, 5, 1, 4, 2, 7, 0, 11, 6});
    }
    void TearDown() override
    {
        bstree_destroy(l0);
        bstree_destroy(l1);
        bstree_destroy(l2);
        bstree_destroy(l3);
        bstree_destroy(l4);

        bstree_destroy(t5);
        bstree_destroy(t6);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;

    inode* t5;
    inode* t6;
};

TEST_F(bstreeIntTest, Find)
{
    ASSERT_TRUE(bstree_find(l0, 1) == nullptr);
    ASSERT_TRUE(bstree_find(l1, 1) != nullptr);
    ASSERT_TRUE(bstree_find(l2, 2) != nullptr);
    ASSERT_TRUE(bstree_find(l3, 3) != nullptr);

    ASSERT_TRUE(bstree_find(t5, 2) != nullptr);
}

TEST_F(bstreeIntTest, FindParent)
{
    ASSERT_TRUE(bstree_find_parent(l0, static_cast<inode*>(nullptr)) == nullptr);
    ASSERT_TRUE(bstree_find_parent(l1, l1) == nullptr);

    auto t6_5 = bstree_find(t6, 5);
    auto t6_7 = bstree_find(t6, 7);
    ASSERT_TRUE(bstree_find_parent(t6, t6_7) == t6_5);
}

TEST_F(bstreeIntTest, FindSuccessor)
{
    ASSERT_TRUE(bstree_find_successor(l0, static_cast<inode*>(nullptr)) == nullptr);
    ASSERT_TRUE(bstree_find_successor(l1, l1) == nullptr);

    auto t6_4 = bstree_find(t6, 4);
    auto t6_5 = bstree_find(t6, 5);
    auto t6_6 = bstree_find(t6, 6);
    auto t6_7 = bstree_find(t6, 7);
    auto t6_11 = bstree_find(t6, 11);
    ASSERT_TRUE(bstree_find_successor(t6, t6) == t6_4);
    ASSERT_TRUE(bstree_find_successor(t6, t6_4) == nullptr);
    ASSERT_TRUE(bstree_find_successor(t6, t6_5) == t6_6);
    ASSERT_TRUE(bstree_find_successor(t6, t6_7) == t6_11);
}


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

TEST_F(bstreeIntTest, Clone)
{
    auto c_l0 = bstree_clone(l0);
    ASSERT_TRUE(bstree_to_string(c_l0) == "");
    bstree_destroy(c_l0);

    auto c_l1 = bstree_clone(l1);
    ASSERT_TRUE(bstree_to_string(c_l1) == "1,");
    bstree_destroy(c_l1);

    auto c_l2 = bstree_clone(l2);
    ASSERT_TRUE(bstree_to_string(c_l2) == "1,2,");
    bstree_destroy(c_l2);

    auto c_t5 = bstree_clone(t5);
    ASSERT_TRUE(bstree_to_string(c_t5) == "3,1,0,2,5,4,7,");
    bstree_destroy(c_t5);
}

