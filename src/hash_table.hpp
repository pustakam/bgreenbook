#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__

#include <unordered_map>
#include <list>

/**
 * Most Recently Used Cache
 *
 * If size goes beyond bound, least recently used item is evicted
 *
 */

template <typename KeyT, typename ValueT, std::size_t bound>
class MruCache
{
    static_assert(bound > 0, "bound greater than 0");

public:
    using key_type = KeyT;
    using value_type = ValueT;
    using item_type = std::pair<key_type, value_type>; 
    using list_type = std::list<const item_type*>;
    using map_type = std::unordered_map<key_type, typename list_type::iterator>;

public:
    MruCache() = default;
    ~MruCache() = default;
    MruCache(const MruCache&) = delete;
    MruCache& operator=(const MruCache&) = delete;
    MruCache(MruCache&&) = delete;
    MruCache& operator=(MruCache&&) = delete;

    void store(const item_type* item)
    {
        // Delete any existing item with the same key
        auto old_it = map_.find(item->first);
        if (old_it != map_.end())
        {
            list_.erase(old_it->second);
            map_.erase(item->first);
        }

        list_.push_front(item);
        map_[item->first] = list_.begin();
        if (list_.size() > bound)
        {
            map_.erase(list_.back()->first);
            list_.pop_back();
        }
    }

    const item_type* find(const key_type& key)
    {
        auto it = map_.find(key);
        if (it == map_.end())
            return nullptr;
        
        // Move the item to the front of the list
        list_.splice(list_.begin(), list_, it->second);
        // it->second (list iterator) stays valid
        return *(it->second);
    }

private:
    list_type list_;
    map_type map_;
};

#endif // __HASH_TABLE_HPP__
