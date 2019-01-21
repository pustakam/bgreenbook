#include <gtest/gtest.h>

#include <iostream>

#include "queue_stack.hpp"

class QueueIntTest : public ::testing::Test
{
protected:
    QueueIntTest()
    {}
    ~QueueIntTest() override = default;

    using QueueInt = Queue<int>;

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    QueueInt q;
};

class StackIntTest : public ::testing::Test
{
protected:
    StackIntTest()
    {}
    ~StackIntTest() override = default;

    using StackInt = Stack<int>;

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    StackInt s;
};


TEST_F(QueueIntTest, All)
{
    ASSERT_TRUE(q.empty());

    q.push(1);
    ASSERT_TRUE(q.top() == 1);
    q.pop();
    ASSERT_TRUE(q.empty());

    q.push({1, 2, 3, 4});
    q.pop();
    ASSERT_TRUE(q.top() == 2); 
    q.pop();
    ASSERT_TRUE(q.top() == 3); 
    q.pop();
    ASSERT_TRUE(q.top() == 4); 
    q.pop();
    ASSERT_TRUE(q.empty());

    q.push({1, 2, 3, 4});
    q.pop();
    q.push({5, 6, 7});
    ASSERT_TRUE(q.top() == 2);
}

TEST_F(StackIntTest, All)
{
    ASSERT_TRUE(s.empty());

    s.push(1);
    ASSERT_TRUE(s.top() == 1);
    s.pop();
    ASSERT_TRUE(s.empty());

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.pop();
    ASSERT_TRUE(s.top() == 3); 
    s.pop();
    ASSERT_TRUE(s.top() == 2); 
    s.pop();
    ASSERT_TRUE(s.top() == 1); 
    s.pop();
    ASSERT_TRUE(s.empty());

    s.push({1, 2, 3, 4});
    s.pop();
    s.push({5, 6, 7});
    s.pop();
    ASSERT_TRUE(s.top() == 6);
}

