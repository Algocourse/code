#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node *left, *right;
    Node *parent;
};

Node* create(int key, Node* parent)
{
    Node* n = new Node();
    n->key = key;
    n->parent = parent;
    n->left = n->right = nullptr;
    return n;
}

Node* add(Node* root, int key)
{
    if (root == nullptr)
    {
        return create(key, nullptr);
    }
    else if (key < root->key)
    {
        if (root->left)
            add(root->left, key);
        else
            root->left = create(key, root);
    }
    else if (key > root->key)
    {
        if (root->right)
            add(root->right, key);
        else
            root->right = create(key, root);
    }
    return root;
}

Node* find(Node* root, int key)
{
    if (root == nullptr)
        return nullptr;
    if (root->key == key)
        return root;
    else if (key < root->key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

int getMin(Node* root)
{
    if (root->left != nullptr)
        return getMin(root->left);
    else
        return root->key;
}

Node* del(Node* root, int key)
{
    Node* n = find(root, key);
    if (n == nullptr)
        return root;
    if (n->left == nullptr && n->right == nullptr)
    {
        if (n->parent == nullptr)
        {
            delete n;
            return nullptr;
        }
        else
        {
            if (n->parent->left == n)
                n->parent->left = nullptr;
            else
                n->parent->right = nullptr;
            delete n;
            return root;
        }
    }
    else if (n->left == nullptr)
    {
        if (n->parent == nullptr)
        {
            Node* result = n->right;
            delete n;
            return result;
        }
        else
        {
            if (n->parent->left == n)
                n->parent->left = n->right;
            else
                n->parent->right = n->right;
            delete n;
            return root;
        }
    }
    else if (n->right == nullptr)
    {
        if (n->parent == nullptr)
        {
            Node* result = n->left;
            delete n;
            return result;
        }
        else
        {
            if (n->parent->left == n)
                n->parent->left = n->left;
            else
                n->parent->right = n->left;
            delete n;
            return root;
        }
    }
    else
    {
        n->key = getMin(n->right);
        n->right = del(n->right, n->key);
        return root;
    }
}

int main()
{
    return 0;
}
