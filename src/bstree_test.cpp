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

TEST_F(bstreeIntTest, Size)
{
    ASSERT_TRUE(bstree_size(l0) == 0);
    ASSERT_TRUE(bstree_size(l1) == 1);
    ASSERT_TRUE(bstree_size(l2) == 2);
    ASSERT_TRUE(bstree_size(l3) == 3);

    ASSERT_TRUE(bstree_size(t5) == 7);
}

TEST_F(bstreeIntTest, SizeIter)
{
    ASSERT_TRUE(bstree_size_iter(l0) == 0);
    ASSERT_TRUE(bstree_size_iter(l1) == 1);
    ASSERT_TRUE(bstree_size_iter(l2) == 2);
    ASSERT_TRUE(bstree_size_iter(l3) == 3);

    ASSERT_TRUE(bstree_size_iter(t5) == 7);
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

TEST_F(bstreeIntTest, RemoveLeaf)
{
    {
        auto c_l1 = bstree_clone(l1);
        auto c_l1_1 = bstree_find(c_l1, 1);
        c_l1 = bstree_remove(c_l1, c_l1_1); 
        ASSERT_TRUE(bstree_to_string(c_l1) == "");
        bstree_destroy(c_l1);
    }
    {
        auto c_l2 = bstree_clone(l2);
        auto c_l2_2 = bstree_find(c_l2, 2);
        c_l2 = bstree_remove(c_l2, c_l2_2); 
        ASSERT_TRUE(bstree_to_string(c_l2) == "1,");
        bstree_destroy(c_l2);
    }
    {
        auto c_t5 = bstree_clone(t5);

        // 0 and 2 are leaves of 1

        auto c_t5_0 = bstree_find(c_t5, 0);
        c_t5 = bstree_remove(c_t5, c_t5_0); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,1,2,5,4,7,");

        auto c_t5_2 = bstree_find(c_t5, 2);
        c_t5 = bstree_remove(c_t5, c_t5_2);
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,1,5,4,7,");

        auto c_t5_1 = bstree_find(c_t5, 1);
        c_t5 = bstree_remove(c_t5, c_t5_1); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,5,4,7,");

        bstree_destroy(c_t5);
    }
}

TEST_F(bstreeIntTest, RemoveNodeWithSingleSubtree)
{
    {
        // 1 is root with 2 in right subtree

        auto c_l2 = bstree_clone(l2);
        auto c_l2_1 = bstree_find(c_l2, 1);
        c_l2 = bstree_remove(c_l2, c_l2_1); 
        ASSERT_TRUE(bstree_to_string(c_l2) == "2,");
        bstree_destroy(c_l2);
    }
    {
        auto c_t5 = bstree_clone(t5);

        // 0 and 2 are leaves of 1

        auto c_t5_0 = bstree_find(c_t5, 0);
        c_t5 = bstree_remove(c_t5, c_t5_0); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,1,2,5,4,7,");

        // 1 has 2 in its right subtree
        auto c_t5_1 = bstree_find(c_t5, 1);
        c_t5 = bstree_remove(c_t5, c_t5_1); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,2,5,4,7,");

        bstree_destroy(c_t5);
    }
}

TEST_F(bstreeIntTest, RemoveNodeWithDoubleSubtree)
{
    {
        auto c_t5 = bstree_clone(t5);
        ASSERT_TRUE(bstree_to_string(c_t5) == "3,1,0,2,5,4,7,");

        // 3 is root, 4 is a leaf successor

        auto c_t5_3 = bstree_find(c_t5, 3);
        c_t5 = bstree_remove(c_t5, c_t5_3); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "4,1,0,2,5,7,");

        // 4 is root, 5 is successor with right subtree
        auto c_t5_4 = bstree_find(c_t5, 4);
        c_t5 = bstree_remove(c_t5, c_t5_4); 
        ASSERT_TRUE(bstree_to_string(c_t5) == "5,1,0,2,7,");

        bstree_destroy(c_t5);
    }

    // Three cases
    // See http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html

    {
        auto tr = bstree_create({6, 2, 1, 9, 8, 15, 13, 11, 18});
        ASSERT_TRUE(bstree_to_string(tr) == "6,2,1,9,8,15,13,11,18,"); 

        auto tr_9 = bstree_find(tr, 9);
        tr = bstree_remove(tr, tr_9);
        ASSERT_TRUE(bstree_to_string(tr) == "6,2,1,11,8,15,13,18,"); 

        ASSERT_TRUE(tr->right->key == 11);
        auto tr_11 = bstree_find(tr, 11);
        ASSERT_TRUE(tr_11->left->key == 8);
        ASSERT_TRUE(tr_11->right->key == 15);

        bstree_destroy(tr);
    }
    {
        auto tr = bstree_create({6, 2, 1, 11, 8, 9, 10, 15});
        ASSERT_TRUE(bstree_to_string(tr) == "6,2,1,11,8,9,10,15,"); 

        auto tr_6 = bstree_find(tr, 6);
        tr = bstree_remove(tr, tr_6);
        ASSERT_TRUE(bstree_to_string(tr) == "8,2,1,11,9,10,15,"); 

        ASSERT_TRUE(tr->key == 8);
        ASSERT_TRUE(tr->right->key == 11);
        auto tr_11 = bstree_find(tr, 11);
        ASSERT_TRUE(tr_11->left->key == 9);
        ASSERT_TRUE(tr_11->right->key == 15);

        bstree_destroy(tr);
    }
    {
        auto tr = bstree_create({6, 2, 1, 4, 11, 15, 17});
        ASSERT_TRUE(bstree_to_string(tr) == "6,2,1,4,11,15,17,"); 

        auto tr_6 = bstree_find(tr, 6);
        tr = bstree_remove(tr, tr_6);
        ASSERT_TRUE(bstree_to_string(tr) == "11,2,1,4,15,17,"); 

        ASSERT_TRUE(tr->key == 11);
        ASSERT_TRUE(tr->right->key == 15);
        auto tr_15 = bstree_find(tr, 15);
        ASSERT_TRUE(tr_15->left == nullptr);
        ASSERT_TRUE(tr_15->right->key == 17);

        bstree_destroy(tr);
    }
}

TEST_F(bstreeIntTest, Balanced)
{
    ASSERT_TRUE(bstree_balanced(l0));
    ASSERT_TRUE(bstree_balanced(l1));
    ASSERT_TRUE(bstree_balanced(l2));
    ASSERT_FALSE(bstree_balanced(l3));
    ASSERT_FALSE(bstree_balanced(l4));

    ASSERT_TRUE(bstree_balanced(t5));
    ASSERT_TRUE(bstree_balanced(t6));
}

