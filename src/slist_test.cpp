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
        l5 = slist_create({1, 2, 3, 4, 5});
    }
    void TearDown() override
    {
        slist_destroy(l0);
        slist_destroy(l1);
        slist_destroy(l2);
        slist_destroy(l3);
        slist_destroy(l4);
        slist_destroy(l5);
    }
    
    inode* l0;
    inode* l1;
    inode* l2;
    inode* l3;
    inode* l4;
    inode* l5;
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

    slist_destroy(sl);
}

TEST_F(SlistIntTest, Clone)
{
    auto cloned_l4 = slist_clone(l4);
    ASSERT_TRUE(slist_equal(l4, cloned_l4));
    ASSERT_FALSE(slist_equal(l3, cloned_l4));

    slist_destroy(cloned_l4);
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

TEST_F(SlistIntTest, MidCounting)
{
    ASSERT_TRUE(slist_mid_by_counting(l0) == nullptr);
    ASSERT_TRUE(slist_mid_by_counting(l1)->data == 1);
    ASSERT_TRUE(slist_mid_by_counting(l2)->data == 1);
    ASSERT_TRUE(slist_mid_by_counting(l3)->data == 2);
    ASSERT_TRUE(slist_mid_by_counting(l4)->data == 2);
    ASSERT_TRUE(slist_mid_by_counting(l5)->data == 3);
}

TEST_F(SlistIntTest, Mid)
{
    ASSERT_TRUE(slist_mid(l0) == nullptr);
    ASSERT_TRUE(slist_mid(l1)->data == 1);
    ASSERT_TRUE(slist_mid(l2)->data == 1);
    ASSERT_TRUE(slist_mid(l3)->data == 2);
    ASSERT_TRUE(slist_mid(l4)->data == 2);
    ASSERT_TRUE(slist_mid(l5)->data == 3);
}

TEST_F(SlistIntTest, KthFromEnd)
{
    ASSERT_TRUE(slist_kth_from_end(l5, 0) == nullptr);
    ASSERT_TRUE(slist_kth_from_end(l5, 1)->data == 1);
    ASSERT_TRUE(slist_kth_from_end(l5, 2)->data == 2);
    ASSERT_TRUE(slist_kth_from_end(l5, 3)->data == 3);
    ASSERT_TRUE(slist_kth_from_end(l5, 4)->data == 4);
    ASSERT_TRUE(slist_kth_from_end(l5, 5)->data == 5);
    ASSERT_TRUE(slist_kth_from_end(l5, 6)->data == 5);

    ASSERT_TRUE(slist_kth_from_end(l4, 0) == nullptr);
    ASSERT_TRUE(slist_kth_from_end(l4, 1)->data == 1);
    ASSERT_TRUE(slist_kth_from_end(l4, 2)->data == 2);
    ASSERT_TRUE(slist_kth_from_end(l4, 3)->data == 3);
    ASSERT_TRUE(slist_kth_from_end(l4, 4)->data == 4);
    ASSERT_TRUE(slist_kth_from_end(l4, 5)->data == 4);

    ASSERT_TRUE(slist_kth_from_end(l2, 0) == nullptr);
    ASSERT_TRUE(slist_kth_from_end(l2, 1)->data == 1);
    ASSERT_TRUE(slist_kth_from_end(l2, 2)->data == 2);
    ASSERT_TRUE(slist_kth_from_end(l2, 3)->data == 2);

    ASSERT_TRUE(slist_kth_from_end(l1, 0) == nullptr);
    ASSERT_TRUE(slist_kth_from_end(l1, 1)->data == 1);
    ASSERT_TRUE(slist_kth_from_end(l1, 2)->data == 1);

    ASSERT_TRUE(slist_kth_from_end(l0, 0) == nullptr);
    ASSERT_TRUE(slist_kth_from_end(l0, 1) == nullptr);
}

TEST_F(SlistIntTest, Merge)
{
    auto c_l0 = slist_clone(l0);
    auto c_l1 = slist_clone(l1);
    auto c_l2 = slist_clone(l2);
    auto c_l3 = slist_clone(l3);
    auto merged_c_l0_c_l3 = slist_merge(c_l0, c_l3);
    auto merged_c_l1_c_l2 = slist_merge(c_l1, c_l2);

    ASSERT_TRUE(merged_c_l0_c_l3 == c_l3);
    ASSERT_TRUE(slist_to_string(merged_c_l0_c_l3) == "head->3->2->1->");
    ASSERT_TRUE(merged_c_l1_c_l2 == c_l1);
    ASSERT_TRUE(slist_to_string(merged_c_l1_c_l2) == "head->1->2->1->");

    slist_destroy(merged_c_l0_c_l3);
    slist_destroy(merged_c_l1_c_l2);
}

TEST_F(SlistIntTest, Palindrome)
{
    ASSERT_TRUE(slist_is_palindrome(l0));
    ASSERT_TRUE(slist_is_palindrome(l1));
    ASSERT_FALSE(slist_is_palindrome(l2));
    ASSERT_FALSE(slist_is_palindrome(l3));
    ASSERT_FALSE(slist_is_palindrome(l4));

    auto p1 = slist_create({1, 1});
    ASSERT_TRUE(slist_is_palindrome(p1));
    auto p2 = slist_create({1, 2, 1});
    ASSERT_TRUE(slist_is_palindrome(p2));
    auto p3 = slist_create({1, 2, 2, 1});
    ASSERT_TRUE(slist_is_palindrome(p3));
    auto np1 = slist_create({1, 2, 3, 1});
    ASSERT_FALSE(slist_is_palindrome(np1));

    slist_destroy(p1);
    slist_destroy(p2);
    slist_destroy(p3);
    slist_destroy(np1);
}

