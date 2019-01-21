#ifndef __MAXHEAP_HPP__
#define __MAXHEAP_HPP__

#include <vector>
#include <algorithm>

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

/**
 * Pass a window of size k through a stream
 * At any time we need to have the top k elements seen so far
 *
 * Use a min heap to keep track of top k elements
 * If new value exceed the minimum, insert into min heap
 */
template <typename T, std::size_t k>
class StreamWindow
{
    static_assert(k > 0, "k greater than 0");

public:
    StreamWindow()
        : topk_heap_{}
    {
        topk_heap_.reserve(k);
    }

    template <typename It>
    StreamWindow(It first, It last)
        : topk_heap_{}
    {
        topk_heap_.reserve(k);

        while (topk_heap_.size() < k && first != last)
        {
            topk_heap_.push_back(*first);
            ++first;
        }
        std::make_heap(topk_heap_.begin(), topk_heap_.end(), std::greater<T>());
    }

    ~StreamWindow() = default;
    StreamWindow(const StreamWindow&) = default;
    StreamWindow& operator=(const StreamWindow&) = default;
    StreamWindow(StreamWindow&&) = default;
    StreamWindow& operator=(StreamWindow&&) = default;

    void process(const T value)
    {
        // We have room to spare
        if (topk_heap_.size() < k)
        {
            topk_heap_.push_back(value);
            std::push_heap(topk_heap_.begin(), topk_heap_.end(), std::greater<T>());
            return;
        }

        // We need to restrict size to k

        // Only insert if value is greater than our min value in min heap
        if (value > topk_heap_.front())
        {
            // Remove the min element
            std::pop_heap(topk_heap_.begin(), topk_heap_.end(), std::greater<T>());

            // min element removed is at topk_heap_.back()
            // Replace with value
            topk_heap_.back() = value;

            // Adjust min heap (heap property) for value
            std::push_heap(topk_heap_.begin(), topk_heap_.end(), std::greater<T>());
        }
    }

    template <typename It>
    void process(It first, It last)
    {
        while (first != last)
        {
            process(*first);
            ++first;
        }
    }

    std::vector<T> topk() const
    {
        std::vector<T> r(topk_heap_.begin(), topk_heap_.end());
        std::sort(r.begin(), r.end());
        return r;
    }

private:
    std::vector<T> topk_heap_; // min heap
};

#endif // __MAXHEAP_HPP__
