#ifndef __BSTREE_HPP__
#define __BSTREE_HPP__

#include <utility>
#include <functional>
#include <initializer_list>
#include <sstream>
#include <queue>
#include <stack>
#include <set>
#include <map>

template <typename T>
struct bstree_node
{
    T key;
    bstree_node* left = nullptr;
    bstree_node* right = nullptr;
};

template <typename T>
bstree_node<T>* bstree_insert(bstree_node<T>* root, T key)
{
    if (nullptr == root)
    {
        return new bstree_node<T>{key, nullptr, nullptr};
    }

    if (key < root->key)
    {
        root->left = bstree_insert(root->left, key);
    }
    else
    {
        root->right = bstree_insert(root->right, key);
    }

    return root;
}

template <typename T>
bstree_node<T>* bstree_create(std::initializer_list<T> l)
{
    bstree_node<T>* root{};
    for (const auto& key : l)
        root = bstree_insert(root, key);

    return root;
}

template <typename T>
void bstree_destroy(bstree_node<T>* root)
{
    if (nullptr == root)
        return;
    if (root->left != nullptr)
        bstree_destroy(root->left);
    if (root->right != nullptr)
        bstree_destroy(root->right);
    
    delete root;
}

template <typename T>
void bstree_preorder(bstree_node<T>* root, std::function<void (bstree_node<T>*)> visit)
{
    if (nullptr == root)
        return;

    visit(root);
    bstree_preorder(root->left, visit);
    bstree_preorder(root->right, visit);
}

template <typename T>
bstree_node<T>* bstree_clone(bstree_node<T>* root)
{
    bstree_node<T>* c_root{};
    if (nullptr == root)
        return c_root;;

    std::function<void (bstree_node<T>*)> insert_node_c_root =
        [&c_root] (bstree_node<T>* node) -> void
        {
            c_root = bstree_insert(c_root, node->key);
        };

    bstree_preorder(root, insert_node_c_root); 
    return c_root;
}

template <typename T>
bstree_node<T>* bstree_find(bstree_node<T>* root, T key)
{
    if (nullptr == root || key == root->key)
        return root;

    return (key < root->key) ? bstree_find(root->left, key) : bstree_find(root->right, key);
}

template <typename T>
bstree_node<T>* bstree_find_parent(bstree_node<T>* root, bstree_node<T>* target)
{
    if (target == root || nullptr == root || nullptr == target)
        return nullptr;

    auto node = root;
    while (node->left != target && node->right != target)
    {
        if (target->key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

// Find the next node for inorder traversal
template <typename T>
bstree_node<T>* bstree_find_successor(bstree_node<T>* root, bstree_node<T>* target)
{
    if (root == nullptr || target == nullptr || target->right == nullptr)
        return nullptr;

    auto node = target->right;
    while (nullptr != node->left)
    {
        node = node->left;
    }
    return node;
}

// Remove target and return new root
// Caller should update root
template <typename T>
bstree_node<T>* bstree_remove(bstree_node<T>* root, bstree_node<T>* target)
{
    if (nullptr == root || nullptr == target)
        return root;

    if (nullptr == target->left && nullptr == target->right)
    {
        if (target != root)
        {
            auto parent = bstree_find_parent(root, target);
            if (parent->left == target)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete target;
        }
        else
        {
            delete root;
            root = nullptr;
        }

        return root;
    }
    else if (nullptr != target->left && nullptr != target->right)
    {
        auto successor = bstree_find_successor(root, target);
        // successor can be a leaf
        // or have a right subtree
        if (successor->right != nullptr)
        {
            auto successor_parent = bstree_find_parent(root, successor);
            std::swap(target->key, successor->key);
            successor_parent->left = successor->right;
            delete successor;
        }
        else
        {
            delete successor;
        }
        return root;
    }

    return root;
}

template <typename T>
int bstree_depth(bstree_node<T>* root)
{
    if (nullptr == root)
        return 0;
    auto left_height = bstree_depth(root->left);  
    auto right_height = bstree_depth(root->right);
    return std::max(left_height, right_height) + 1;
}

template <typename T>
int bstree_depth_iter(bstree_node<T>* root)
{
    if (nullptr == root)
        return 0;

    std::size_t maxdepth{0};
    std::stack<bstree_node<T>*> node_stack;
    std::set<bstree_node<T>*> visited;

    node_stack.push(root);
    while (!node_stack.empty())
    {
        auto node = node_stack.top();

        // Keep pushing on the stack until a leaf node is found
        // The size of the stack at that point is
        //      depth of the leaf from root
        // Take the max of depth for all leaf nodes

        if (nullptr != node->left
                && visited.find(node->left) == visited.end())
        {
            node_stack.push(node->left);
        }
        else if (nullptr != node->right
                && visited.find(node->right) == visited.end())
        {
            node_stack.push(node->right);
        }
        else
        {
            visited.insert(node);
            maxdepth = std::max(maxdepth, node_stack.size());
            node_stack.pop();
        }
    }
    return maxdepth;
}

template <typename T>
void bstree_inorder(bstree_node<T>* root, std::function<void (bstree_node<T>*)> visit)
{
    if (nullptr == root)
        return;

    bstree_inorder(root->left, visit);
    visit(root);
    bstree_inorder(root->right, visit);
}

template <typename T>
void bstree_postorder(bstree_node<T>* root, std::function<void (bstree_node<T>*)> visit)
{
    if (nullptr == root)
        return;

    bstree_postorder(root->left, visit);
    bstree_postorder(root->right, visit);
    visit(root);
}

template <typename T>
std::string bstree_to_string(bstree_node<T>* root)
{
    std::ostringstream ss;
    std::function<void (bstree_node<T>*)> print_node =
        [&ss] (bstree_node<T>* node) -> void
        {
            ss << node->key << ",";
        };

    bstree_preorder(root, print_node); 
    return ss.str();
}

#endif // __BSTREE_HPP__
