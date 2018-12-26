#include <utility>
#include <initializer_list>
#include <sstream>
#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
struct slist_node
{
    T data;
    slist_node* next;
};

template <typename T>
slist_node<T>* insert(slist_node<T>* head, T data)
{
    return new slist_node<T>{data, head};
}

template <typename T>
std::pair<bool, slist_node<T>*>
remove(slist_node<T>* head, slist_node<T>* target)
{
    if (head == nullptr || target == nullptr)
        return make_pair(false, head);

    if (head == target)
    {
        head = head->next;
        delete target;
        return make_ptr(true, head);
    }

    auto before = head;
    while (before && before->next != target)
    {
        before = before->next;
    }
    if (before == nullptr)
        return make_pair(false, head);

    before->next = target->next;
    delete target;
    return make_pair(true, head);
}

template <typename T>
slist_node<T>* find(slist_node<T>* head, T data)
{
    auto node = head;
    while (node && node->data != data)
    {
        node = node->next;
    }
    return node;
}

template <typename T>
slist_node<T>* insert_sorted(slist_node<T>* head, T data)
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
slist_node<T>* tail(slist_node<T>* head)
{
    if (head == nullptr)
        return nullptr;

    auto tail = head;
    while (tail->next != nullptr)
        tail = tail->next;

    return tail;
}

template <typename T>
slist_node<T>* reverse(slist_node<T>* head)
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
slist_node<T>* create(initializer_list<T> l)
{
    slist_node<T>* head{};
    for (const auto& data : l)
        head = insert(head, data);

    return head;
}

template <typename T>
slist_node<T>* clone(slist_node<T>* head)
{
    decltype(head) h{};
    auto current = head; 
    while (current != nullptr)
    {
        h = insert(h, current->data);
        current = current->next;
    }

    return reverse(h);
}

template <typename T>
string to_string(slist_node<T>* head)
{
    ostringstream ss;
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
bool are_equal(slist_node<T>* head1, slist_node<T>* head2)
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

int main(int argc, char* argv[])
{
    using inode = slist_node<int>;
    inode* l0 = create<int>({});
    cout << to_string(l0) << endl;
    inode* l1 = create({1});
    cout << to_string(l1) << endl;
    inode* l2 = create({1, 2});
    cout << to_string(l2) << endl;
    inode* l3 = create({1, 2, 3});
    cout << to_string(l3) << endl;
    inode* l4 = create({1, 2, 3, 4});
    cout << to_string(l4) << endl;

    /*
    cout << to_string(reverse(l0)) << endl;
    cout << to_string(reverse(l1)) << endl;
    cout << to_string(reverse(l2)) << endl;
    cout << to_string(reverse(l3)) << endl;
    cout << to_string(reverse(l4)) << endl;
    */
    auto cloned_l4 = clone(l4);
    cout << to_string(cloned_l4) << endl;
    assert(are_equal(l4, cloned_l4));
    assert(!are_equal(l3, cloned_l4));

    return 0;
}

