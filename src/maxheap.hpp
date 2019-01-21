#ifndef __MAXHEAP_HPP__
#define __MAXHEAP_HPP__

std::size_t lchild_index(const std::size_t i)
{
    return 2*i + 1;
}
std::size_t rchild_index(const std::size_t i)
{
    return 2*i + 2;
}
std::size_t parent_index(const std::size_t i)
{
    if (i == 0)
        return 0;

    return (i - 1)/2;
}

template <typename T>
void heapify_max(std::vector<T>& array)
{
    for (auto it=array.begin(); it != array.end(); ++it)
    {
        std::size_t i = it - array.begin();
        std::size_t p_i = parent_index(i);
        while (i >= 0 && array[p_i] < array[i])
        {
            std::swap(array[p_i], array[i]);
            i = p_i;
            p_i = parent_index(i);
        }
    }
}

template <typename T>
T find_max(const std::vector<T>& max_heap)
{
    return max_heap[0];
}

template <typename T>
void remove_max(std::vector<T>& max_heap)
{
    // Swap the root with the last
    // Restore heap property

    std::swap(*(max_heap.begin()), *(max_heap.end() - 1));
    max_heap.erase(max_heap.end() - 1);

    std::size_t i{};
    while (i < max_heap.size())
    {
        // Find the index of the child to swap

        auto ci = lchild_index(i);
        if (ci >= max_heap.size())
        {
            break;
        }

        auto ri = rchild_index(i);
        if (ri < max_heap.size() && max_heap[ri] > max_heap[ci])
        {
            ci = ri;
        }

        if (max_heap[i] >= max_heap[ci])
        {
            break;
        }

        std::swap(max_heap[i], max_heap[ci]);
        i = ci;
    }
}

template <typename T>
void insert_max(std::vector<T>& max_heap, T key)
{
    max_heap.push_back(key);
    auto i = max_heap.size() - 1;
    auto p_i = parent_index(i);
    while (i > 0 && max_heap[p_i] < max_heap[i])
    {
        std::swap(max_heap[p_i], max_heap[i]);
        i = p_i;
        p_i = parent_index(i);
    }
}

#endif // __MAXHEAP_HPP__
