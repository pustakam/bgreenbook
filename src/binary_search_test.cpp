#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "binary_search.hpp"

TEST(BinarySearchTest, Empty)
{
    std::vector<int> v{};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 5) == v.end());
}

TEST(BinarySearchTest, One)
{
    std::vector<int> v{1};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 1) == v.begin());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 5) == v.end());
}

TEST(BinarySearchTest, Two)
{
    std::vector<int> v{1, 2};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 1) == v.begin());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 2) == (v.begin() + 1));
    ASSERT_TRUE(bserch(v.begin(), v.end(), 5) == v.end());
}

TEST(BinarySearchTest, Ten)
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 1) == v.begin());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 2) == v.begin() + 1);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 3) == v.begin() + 2);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 4) == v.begin() + 3);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 5) == v.begin() + 4);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 6) == v.begin() + 5);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 7) == v.begin() + 6);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 8) == v.begin() + 7);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 9) == v.begin() + 8);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 10) == v.begin() + 9);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 11) == v.end());
}

TEST(BinarySearchTest, duplicates_start)
{
    std::vector<int> v{1, 1, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 1) == v.begin());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 15) == v.end());
}

TEST(BinarySearchTest, duplicates_end)
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 13, 13};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 13) == v.begin() + 10);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 15) == v.end());
}

TEST(BinarySearchTest, duplicates_middle)
{
    std::vector<int> v{1, 2, 3, 4, 5, 5, 5, 5, 9, 10, 11, 12, 13};
    ASSERT_TRUE(bserch(v.begin(), v.end(), -1) == v.end());
    ASSERT_TRUE(bserch(v.begin(), v.end(), 5) == v.begin() + 4);
    ASSERT_TRUE(bserch(v.begin(), v.end(), 15) == v.end());
}

