#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <functional>

#include "graph_search.hpp"

using intvertex = vertex<int>;

void intvertex_printer(const intvertex* vt)
{
    std::cout << vt->value << ", " << '\n';
}

class GraphIntTest : public ::testing::Test
{
protected:
    GraphIntTest()
    {}
    ~GraphIntTest() override = default;

    void SetUp() override
    {
        for (int i=0; i<10; ++i)
            v.push_back(new intvertex{i, {}});

        auto add_neighbors = [](intvertex* vt, std::initializer_list<intvertex*> l) -> void
        {
            vt->neighbors.insert(vt->neighbors.end(), l);
        };

        // See the German cities graph at https://en.wikipedia.org/wiki/Breadth-first_search
        add_neighbors(v[0], {v[1], v[2], v[3]});
        add_neighbors(v[1], {v[0], v[4]});
        add_neighbors(v[2], {v[0], v[5], v[6]});
        add_neighbors(v[3], {v[0], v[9]});
        add_neighbors(v[4], {v[1], v[7]});
        add_neighbors(v[5], {v[2]});
        add_neighbors(v[6], {v[2], v[8], v[9]});
        add_neighbors(v[7], {v[4], v[9]});
        add_neighbors(v[8], {v[6]});
        add_neighbors(v[9], {v[7], v[6], v[3]});
    }

    void TearDown() override
    {
        for (auto vt : v)
            delete vt;
    }

    std::vector<intvertex*> v;
};

TEST_F(GraphIntTest, bfs)
{
    bfs(v[0], visitor<intvertex>(intvertex_printer));
}

TEST_F(GraphIntTest, dfs)
{
    dfs(v[0], visitor<intvertex>(intvertex_printer));
}

