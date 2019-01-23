#ifndef __BINARY_SEARCH_HPP__
#define __BINARY_SEARCH_HPP__

#include <iterator>
#include <cassert>
#include <iostream>

/**
 * Iter is a random iterator
 * [first, last) is a sorted range
 */
template <typename Iter>
Iter bserch_impl
(
    Iter first,
    Iter last,
    const typename std::iterator_traits<Iter>::value_type& key,
    std::random_access_iterator_tag
)
{
    if (first >= last)
        return last;

    auto lower = first;
    auto upper = last - 1;

    while (lower < upper && key != *lower)
    {
        auto mid = lower + (upper - lower)/2;
        if (key <= *mid)
            upper = mid;
        else
            lower = mid + 1;
    }
    if (key == *lower)
        return lower;

    // Not found
    return last;
}

template <typename Iter>
Iter bserch
(
    Iter first,
    Iter last,
    const typename std::iterator_traits<Iter>::value_type& key
)
{
    // Use tag dispatching to enforce random access iterator etc
    auto it_cat = typename std::iterator_traits<Iter>::iterator_category();
    return bserch_impl(first, last, key, it_cat);
}

#endif // __BINARY_SEARCH_HPP__
