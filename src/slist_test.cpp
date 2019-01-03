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
        l0 = slist_create<int>({});
        l1 = slist_create({1});
        l2 = slist_create({1, 2});
        l3 = slist_create({1, 2, 3});
        l4 = slist_create({1, 2, 3, 4});
    }
    void TearDown() override
    {
        slist_destroy(l0);
        slist_destroy(l1);
        slist_destroy(l2);
        slist_destroy(l3);
        slist_destroy(l4);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;
};

TEST_F(SlistIntTest, Find)
{
    ASSERT_TRUE(slist_find(l4, 4) == l4);
    ASSERT_TRUE(slist_find(l4, 2) == l4->next->next);
    ASSERT_TRUE(slist_tail(l4) && slist_tail(l4)->data == 1);
    ASSERT_TRUE(slist_find(l4, 1) == slist_tail(l4));
    ASSERT_TRUE(slist_find(l4, -1) == nullptr);
}

TEST_F(SlistIntTest, InsertSorted)
{
    auto sl = slist_create({7, 3, 1, 0, -6});
    ASSERT_TRUE(slist_to_string(sl) == "head->-6->0->1->3->7->");

    // before head
    sl = slist_insert_sorted(sl, -9); 
    ASSERT_TRUE(sl && slist_to_string(sl) == "head->-9->-6->0->1->3->7->");

    // in the middle
    sl = slist_insert_sorted(sl, 2); 
    ASSERT_TRUE(sl && slist_to_string(sl) == "head->-9->-6->0->1->2->3->7->");

    // last
    sl = slist_insert_sorted(sl, 9); 
    ASSERT_TRUE(sl && slist_to_string(sl) == "head->-9->-6->0->1->2->3->7->9->");

    // multiple
    sl = slist_insert_sorted(sl, 9); 
    ASSERT_TRUE(sl && slist_to_string(sl) == "head->-9->-6->0->1->2->3->7->9->9->");
}

TEST_F(SlistIntTest, Clone)
{
    auto cloned_l4 = slist_clone(l4);
    ASSERT_TRUE(slist_equal(l4, cloned_l4));
    ASSERT_FALSE(slist_equal(l3, cloned_l4));
}

TEST_F(SlistIntTest, Remove)
{
    auto cloned_l4 = slist_clone(l4);
    // head->4->3->2->1->

    // remove middle node
    auto p = slist_remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(slist_to_string(cloned_l4) == "head->4->2->1->");

    // remove head
    p = slist_remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(slist_to_string(cloned_l4) == "head->2->1->");

    // remove tail
    p = slist_remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(slist_to_string(cloned_l4) == "head->2->");

    // remove last
    p = slist_remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(slist_to_string(cloned_l4) == "head->");
}


