#ifndef __SLIST_H__
#define __SLIST_H__

#include <utility>
#include <initializer_list>
#include <sstream>

template <typename T>
struct slist_node
{
    T data;
    slist_node* next;
};

template <typename T>
slist_node<T>* slist_insert(slist_node<T>* head, T data)
{
    return new slist_node<T>{data, head};
}

template <typename T>
std::pair<bool, slist_node<T>*>
slist_remove(slist_node<T>* head, slist_node<T>* target)
{
    if (head == nullptr || target == nullptr)
        return std::make_pair(false, head);

    if (head == target)
    {
        head = head->next;
        delete target;
        return std::make_pair(true, head);
    }

    auto before = head;
    while (before && before->next != target)
    {
        before = before->next;
    }
    if (before == nullptr)
        return std::make_pair(false, head);

    before->next = target->next;
    delete target;
    return std::make_pair(true, head);
}

template <typename T>
slist_node<T>* slist_find(slist_node<T>* head, T data)
{
    auto node = head;
    while (node && node->data != data)
    {
        node = node->next;
    }
    return node;
}

template <typename T>
slist_node<T>* slist_insert_sorted(slist_node<T>* head, T data)
{
    if (head == nullptr)
        return new slist_node<T>{data, nullptr};

    if (data <= head->data)
        return new slist_node<T>{data, head};

    auto before = head;
    // After the end of the loop, data <= before->next->data
    // Or before->next == nullptr
    while (before->next && data > before->next->data)
    {
        before = before->next;
    }
    auto node = new slist_node<T>{data, before->next};
    before->next = node;

    return head;
}

template <typename T>
slist_node<T>* slist_tail(slist_node<T>* head)
{
    if (head == nullptr)
        return nullptr;

    auto tail = head;
    while (tail->next != nullptr)
        tail = tail->next;

    return tail;
}

template <typename T>
slist_node<T>* slist_reverse(slist_node<T>* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    decltype(head) prev = nullptr;
    decltype(head) after = nullptr;
    auto current = head;
    while (current != nullptr)
    {
        after = current->next;
        current->next = prev;
        prev = current;
        current = after;
    }

    return prev;
}

template <typename T>
slist_node<T>* slist_create(std::initializer_list<T> l)
{
    slist_node<T>* head{};
    for (const auto& data : l)
        head = slist_insert(head, data);

    return head;
}

template <typename T>
void slist_destroy(slist_node<T>* head)
{
    while (head != nullptr)
    {
        auto tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
slist_node<T>* slist_clone(slist_node<T>* head)
{
    decltype(head) h{};
    auto current = head; 
    while (current != nullptr)
    {
        h = slist_insert(h, current->data);
        current = current->next;
    }

    return slist_reverse(h);
}

template <typename T>
std::string slist_to_string(slist_node<T>* head)
{
    std::ostringstream ss;
    ss << "head->";
    auto node = head;
    while (node)
    {
        ss << node->data << "->";
        node = node->next;
    }
    return ss.str();
}

template <typename T>
bool slist_equal(slist_node<T>* head1, slist_node<T>* head2)
{
    auto node1 = head1;
    auto node2 = head2;
    while (node1 && node2 && node1->data == node2->data)
    {
        node1 = node1->next;
        node2 = node2->next;
    }

    return node1 == nullptr && node2 == nullptr;
}

template <typename T>
slist_node<T>* slist_mid_by_counting(slist_node<T>* head)
{
    // Count the number of nodes
    int count = 0;
    auto node = head;
    while (node != nullptr)
    {
        ++count;
        node = node->next;
    }

    auto mid = count/2;
    node = head;
    while (mid)
    {
        node = node->next;
        --mid;
    }
    return node;
}

template <typename T>
slist_node<T>* slist_mid(slist_node<T>* head)
{
    auto leading = head;
    auto trailing = head;
    // leading moves 2 steps for trailing 1 step
    while (leading != nullptr)
    {
        leading = leading->next;
        if (leading != nullptr)
        {
            leading = leading->next;
            trailing = trailing->next;
        }
    }
    return trailing;
}

template <typename T>
slist_node<T>* slist_kth_from_end(slist_node<T>* head, std::size_t k)
{
    auto leading = head;
    auto trailing = head;
    while (k && leading != nullptr)
    {
        leading = leading->next;
        --k;
    }
    // At this point leading is (size - k) steps away from end of list
    // So match each step of leading with trailing until leading reaches
    // end of list
    while (leading != nullptr) 
    {
        leading = leading->next;
        trailing = trailing->next;
    }
    return trailing;
}

template <typename T>
slist_node<T>* slist_merge(slist_node<T>* head1, slist_node<T>* head2)
{
    if (head1 == nullptr || head2 == nullptr)
    {
        return head1 ? head1 : head2;
    }

    auto node = head1;
    while (node->next != nullptr)
        node = node->next;

    node->next = head2;
    return head1;
}

#endif // __SLIST_H__

