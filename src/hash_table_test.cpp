#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "hash_table.hpp"

TEST(MruCacheTest, Size1)
{
    MruCache<int, int, 1> mc;

    ASSERT_TRUE(mc.find(33) == nullptr);
    auto pair_33 = std::make_unique<decltype(mc)::item_type>(33, 33); 
    mc.store(pair_33.get());
    ASSERT_TRUE(mc.find(33) == pair_33.get());

    ASSERT_TRUE(mc.find(44) == nullptr);
    auto pair_44 = std::make_unique<decltype(mc)::item_type>(44, 44); 
    mc.store(pair_44.get());
    ASSERT_TRUE(mc.find(44) == pair_44.get());
}

TEST(MruCacheTest, Size2)
{
    MruCache<int, int, 2> mc;

    auto pair_33 = std::make_unique<decltype(mc)::item_type>(33, 33); 
    auto pair_44 = std::make_unique<decltype(mc)::item_type>(44, 44); 
    auto pair_55 = std::make_unique<decltype(mc)::item_type>(55, 55); 
    auto pair_66 = std::make_unique<decltype(mc)::item_type>(66, 66); 

    mc.store(pair_33.get());
    ASSERT_TRUE(mc.find(33) == pair_33.get());

    mc.store(pair_44.get());
    ASSERT_TRUE(mc.find(44) == pair_44.get());

    mc.store(pair_55.get());
    ASSERT_TRUE(mc.find(33) == nullptr);
    ASSERT_TRUE(mc.find(44) == pair_44.get());
    ASSERT_TRUE(mc.find(55) == pair_55.get());

    mc.store(pair_66.get());
    ASSERT_TRUE(mc.find(44) == nullptr);
    ASSERT_TRUE(mc.find(55) == pair_55.get());
    ASSERT_TRUE(mc.find(66) == pair_66.get());
}

