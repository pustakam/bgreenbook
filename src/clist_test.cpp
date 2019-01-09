#include <gtest/gtest.h>

#include "clist.hpp"

class clistIntTest : public ::testing::Test
{
protected:
    clistIntTest()
        : l0{}, l1{}, l2{}, l3{}, l4{}
    {}
    ~clistIntTest() override = default;

    using inode = clist_node<int>;

    void SetUp() override
    {
        l0 = clist_create<int>({});
        l1 = clist_create({1});
        l2 = clist_create({1, 2});
        l3 = clist_create({1, 2, 3});
        l4 = clist_create({1, 2, 3, 4});
    }
    void TearDown() override
    {
        clist_destroy(l0);
        clist_destroy(l1);
        clist_destroy(l2);
        clist_destroy(l3);
        clist_destroy(l4);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;
};

TEST_F(clistIntTest, Find)
{
    ASSERT_TRUE(clist_find(l4, 4) == l4);
    ASSERT_TRUE(clist_find(l4, 2) == l4->next->next);
    ASSERT_TRUE(clist_tail(l4) && clist_tail(l4)->data == 1);
    ASSERT_TRUE(clist_find(l4, 1) == clist_tail(l4));
    ASSERT_TRUE(clist_find(l4, -1) == nullptr);
}

TEST_F(clistIntTest, ToString)
{
    ASSERT_TRUE(clist_to_string(l4) == "head->4->3->2->1->head");
    ASSERT_TRUE(clist_to_string(l3) == "head->3->2->1->head");
    ASSERT_TRUE(clist_to_string(l2) == "head->2->1->head");
    ASSERT_TRUE(clist_to_string(l1) == "head->1->head");
    ASSERT_TRUE(clist_to_string(l0) == "head->");
}

TEST_F(clistIntTest, Clone)
{
    auto c_l4 = clist_clone(l4);
    ASSERT_TRUE(clist_to_string(c_l4) == "head->4->3->2->1->head");
    auto c_l3 = clist_clone(l3);
    ASSERT_TRUE(clist_to_string(c_l3) == "head->3->2->1->head");
    auto c_l2 = clist_clone(l2);
    ASSERT_TRUE(clist_to_string(c_l2) == "head->2->1->head");
    auto c_l1 = clist_clone(l1);
    ASSERT_TRUE(clist_to_string(c_l1) == "head->1->head");
    auto c_l0 = clist_clone(l0);
    ASSERT_TRUE(clist_to_string(c_l0) == "head->");

    clist_destroy(c_l4);
    clist_destroy(c_l3);
    clist_destroy(c_l2);
    clist_destroy(c_l1);
    clist_destroy(c_l0);
}

TEST_F(clistIntTest, Remove)
{
    auto cloned_l4 = clist_clone(l4);

    // remove middle node
    auto p = clist_remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(clist_to_string(cloned_l4) == "head->4->2->1->head");

    // remove head
    p = clist_remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(clist_to_string(cloned_l4) == "head->2->1->head");

    // remove tail
    p = clist_remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(clist_to_string(cloned_l4) == "head->2->head");

    // remove last
    p = clist_remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(clist_to_string(cloned_l4) == "head->");
}

