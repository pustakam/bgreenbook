#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "maxheap.hpp"

class MaxHeapIntTest : public ::testing::Test
{
protected:
    MaxHeapIntTest()
    {}
    ~MaxHeapIntTest() override = default;

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(MaxHeapIntTest, Indices)
{
    ASSERT_TRUE(lchild_index(0) == 1);
    ASSERT_TRUE(rchild_index(0) == 2);
    ASSERT_TRUE(parent_index(1) == 0);
    ASSERT_TRUE(parent_index(2) == 0);

    ASSERT_TRUE(lchild_index(1) == 3);
    ASSERT_TRUE(rchild_index(1) == 4);
    ASSERT_TRUE(parent_index(3) == 1);
    ASSERT_TRUE(parent_index(4) == 1);

    ASSERT_TRUE(lchild_index(2) == 5);
    ASSERT_TRUE(rchild_index(2) == 6);
    ASSERT_TRUE(parent_index(5) == 2);
    ASSERT_TRUE(parent_index(6) == 2);
}

TEST_F(MaxHeapIntTest, HeapifyMaxRemoveMax)
{
    std::vector<int> a{6, 7, 4, 9, 10, 1, 3, 6};
    heapify_max(a);

    ASSERT_TRUE(find_max(a) == 10);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 9);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 7);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 6);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 6);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 4);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 3);
    remove_max(a);

    ASSERT_TRUE(find_max(a) == 1);
    remove_max(a);
}

TEST_F(MaxHeapIntTest, InsertMaxRemoveMax)
{
    std::vector<int> b{6, 7, 4, 9, 10, 1, 3, 6};
    heapify_max(b);

    std::vector<int> a{};

    insert_max(a, 6);
    ASSERT_TRUE(find_max(a) == 6);

    insert_max(a, 7);
    ASSERT_TRUE(find_max(a) == 7);

    insert_max(a, 4);
    ASSERT_TRUE(find_max(a) == 7);

    insert_max(a, 9);
    ASSERT_TRUE(find_max(a) == 9);

    insert_max(a, 10);
    ASSERT_TRUE(find_max(a) == 10);

    insert_max(a, 1);
    ASSERT_TRUE(find_max(a) == 10);

    insert_max(a, 3);
    ASSERT_TRUE(find_max(a) == 10);

    insert_max(a, 6);
    ASSERT_TRUE(find_max(a) == 10);

    ASSERT_TRUE(a == b);
}

TEST(StreamWindowTest, All)
{
    {
        StreamWindow<int, 1> w;
        w.process(2);
        ASSERT_TRUE(w.topk() == std::vector<int>({2}));
        w.process(0);
        ASSERT_TRUE(w.topk() == std::vector<int>({2}));
        w.process(3);
        ASSERT_TRUE(w.topk() == std::vector<int>({3}));
    }

    {
        StreamWindow<int, 2> w;
        w.process(10);
        ASSERT_TRUE(w.topk() == std::vector<int>({10}));
        w.process(1);
        ASSERT_TRUE(w.topk() == std::vector<int>({1, 10}));
        w.process(3);
        ASSERT_TRUE(w.topk() == std::vector<int>({3, 10}));
        w.process(2);
        ASSERT_TRUE(w.topk() == std::vector<int>({3, 10}));
        w.process(11);
        ASSERT_TRUE(w.topk() == std::vector<int>({10, 11}));
    }

    {
        std::vector<int> input{1, 2, 3};
        StreamWindow<int, 3> w(input.begin(), input.end());
        ASSERT_TRUE(w.topk() == std::vector<int>({1, 2, 3}));
        w.process(4);
        ASSERT_TRUE(w.topk() == std::vector<int>({2, 3, 4}));
        w.process(1);
        ASSERT_TRUE(w.topk() == std::vector<int>({2, 3, 4}));
    }
    {
        std::vector<int> input{1, 2, 3};
        StreamWindow<int, 4> w(input.begin(), input.end());
        w.process(4);
        ASSERT_TRUE(w.topk() == std::vector<int>({1, 2, 3, 4}));
        w.process(5);
        ASSERT_TRUE(w.topk() == std::vector<int>({2, 3, 4, 5}));

        std::vector<int> another_input{5, 5, 5, 5};
        w.process(another_input.begin(), another_input.end());
        ASSERT_TRUE(w.topk() == std::vector<int>({5, 5, 5, 5}));
    }

}
