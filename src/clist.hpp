#ifndef __CLIST_H__
#define __CLIST_H__

#include <utility>
#include <initializer_list>
#include <sstream>

template <typename T>
struct clist_node
{
    T data;
    clist_node* next;
};

// node is always inserted "before head"
template <typename T>
clist_node<T>* clist_insert(clist_node<T>* head, T data)
{
    auto node = new clist_node<T>{data, nullptr}; 
    if (head == nullptr)
    {
        node->next = node;
        return node;
    }
    else if (head == head->next)
    {
        node->next = head;
        head->next = node;
        return node;
    }

    // insert after head and then swap values with head
    // this avoids a loop
    node->next = head->next;
    head->next = node;
    std::swap(head->data, node->data);
    return head;
}

template <typename T>
std::pair<bool, clist_node<T>*>
clist_remove(clist_node<T>* head, clist_node<T>* target)
{
    if (head == nullptr || target == nullptr)
        return std::make_pair(false, head);

    // Do we have to remove head?
    if (head == target)
    {
        // One node clist
        if (head == head->next)
        {
            delete head;
            return std::make_pair(true, nullptr);
        }

        // Avoid iterating to tail?
        //
        // Swap the values of head and the node after head
        // Then remove the node after head
        auto after = head->next;
        std::swap(after->data, head->data);
        head->next = after->next;
        delete after;
        return std::make_pair(true, head);
    }


    // This covers the case where head != target
    auto before = head;
    while (before->next != head && before->next != target)
    {
        before = before->next;
    }
    if (before->next == head)
        return std::make_pair(false, head);

    // We found the target
    before->next = target->next;
    delete target;
    return std::make_pair(true, head);
}

template <typename T>
clist_node<T>* clist_find(clist_node<T>* head, T data)
{
    if (head == nullptr)
        return head;

    auto node = head;
    while (node->next != head && node->data != data)
    {
        node = node->next;
    }
    if (node->data == data)
        return node;
    return nullptr;
}

template <typename T>
clist_node<T>* clist_create(std::initializer_list<T> l)
{
    clist_node<T>* head{};
    for (const auto& data : l)
        head = clist_insert(head, data);

    return head;
}

template <typename T>
void clist_destroy(clist_node<T>* head)
{
    while (head != nullptr)
    {
        head = clist_remove(head, head).second;
    }
}

template <typename T>
std::string clist_to_string(clist_node<T>* head)
{
    std::ostringstream ss;
    ss << "head->";
    if (head == nullptr)
        return ss.str();

    auto node = head;
    do
    {
        ss << node->data << "->";
        node = node->next;
    }
    while (node != head);

    ss << "head";
    return ss.str();
}

template <typename T>
clist_node<T>* clist_tail(clist_node<T>* head)
{
    if (head == nullptr || head->next == head)
        return head;

    auto tail = head;
    while (tail->next != head)
        tail = tail->next;

    return tail;
}

template <typename T>
clist_node<T>* clist_reverse(clist_node<T>* head)
{
    if (head == nullptr || head->next == head)
        return head;

    decltype(head) prev = nullptr;
    auto current = head;
    decltype(head) after = nullptr;
    // clist will flatten out and lose its loop
    do
    {
        after = current->next;
        current->next = prev;
        prev = current;
        current = after;
    }
    while (current != head);
    // Restore loop
    //
    // At this point head->next is nullptr, set it to the new head
    head->next = prev;

    return prev;
}

template <typename T>
clist_node<T>* clist_clone(clist_node<T>* head)
{
    if (head == nullptr)
        return nullptr;

    decltype(head) h{};
    auto current = head; 
    do
    {
        h = clist_insert(h, current->data);
        current = current->next;
    }
    while (current != head);

    return clist_reverse(h);
}


#endif // __CLIST_H__

