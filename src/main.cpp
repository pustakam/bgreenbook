#include <iostream>
#include <cassert>

#include "slist.hpp"

int main(int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    using namespace std;

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

