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

TEST_F(SlistIntTest, Find)
{
    ASSERT_TRUE(find(l4, 4) == l4);
    ASSERT_TRUE(find(l4, 2) == l4->next->next);
    ASSERT_TRUE(tail(l4) && tail(l4)->data == 1);
    ASSERT_TRUE(find(l4, 1) == tail(l4));
    ASSERT_TRUE(find(l4, -1) == nullptr);
}

TEST_F(SlistIntTest, InsertSorted)
{
    auto sl = create({7, 3, 1, 0, -6});
    ASSERT_TRUE(to_string(sl) == "head->-6->0->1->3->7->");

    // before head
    sl = insert_sorted(sl, -9); 
    ASSERT_TRUE(sl && to_string(sl) == "head->-9->-6->0->1->3->7->");

    // in the middle
    sl = insert_sorted(sl, 2); 
    ASSERT_TRUE(sl && to_string(sl) == "head->-9->-6->0->1->2->3->7->");

    // last
    sl = insert_sorted(sl, 9); 
    ASSERT_TRUE(sl && to_string(sl) == "head->-9->-6->0->1->2->3->7->9->");

    // multiple
    sl = insert_sorted(sl, 9); 
    ASSERT_TRUE(sl && to_string(sl) == "head->-9->-6->0->1->2->3->7->9->9->");
}

TEST_F(SlistIntTest, Clone)
{
    auto cloned_l4 = clone(l4);
    ASSERT_TRUE(are_equal(l4, cloned_l4));
    ASSERT_FALSE(are_equal(l3, cloned_l4));
}

TEST_F(SlistIntTest, Remove)
{
    auto cloned_l4 = clone(l4);
    // head->4->3->2->1->

    // remove middle node
    auto p = remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(to_string(cloned_l4) == "head->4->2->1->");

    // remove head
    p = remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(to_string(cloned_l4) == "head->2->1->");

    // remove tail
    p = remove(cloned_l4, cloned_l4->next);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(to_string(cloned_l4) == "head->2->");

    // remove last
    p = remove(cloned_l4, cloned_l4);
    ASSERT_TRUE(p.first);
    cloned_l4 = p.second;
    ASSERT_TRUE(to_string(cloned_l4) == "head->");
}


