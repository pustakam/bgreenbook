#ifndef __GRAPH_SEARCH_HPP__
#define __GRAPH_SEARCH_HPP__

#include <functional>
#include <vector>
#include <set>
#include <queue>

template <typename T>
struct vertex
{
    T value;
    std::vector<vertex<T>*> neighbors;
};

template <typename V>
using visitor = std::function<void (V*)>;

template <typename T>
void bfs(vertex<T>* origin, visitor<vertex<T>> visit)
{
    std::queue<const vertex<T>*> q;
    std::set<const vertex<T>*> visited;

    visit(origin);
    visited.insert(origin);
    q.push(origin);

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (auto v : u->neighbors)
        {
            if (visited.find(v) == visited.end())
            {
                visit(v);
                visited.insert(v);
                q.push(v);
            }
        }
    }
}

#endif
