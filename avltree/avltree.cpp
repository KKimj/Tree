#include "avltree.h"
#include <cstdio>
#include <cstdlib>



void Avltree::print(char* filepath)
{
    this->out = fopen(filepath, "w");
    _traversal(this->root);
    fclose(this->out);
}

int Avltree::insert(int value)
{
    this->root = _insert(this->root, value, value);
    this->count++;
    return value;
}
int Avltree::search(int key)
{
    return this->_search(key);
}
void Avltree::deleteNode(int key)
{
    this->root = _delete(this->root, key);
}



void Avltree::_traversal(Node* node)
{
    if (node == nullptr) return;

    _traversal(node->left);
    fprintf(this->out, "%d ", node->value);
#ifdef VERBOSE
    fprintf((FILE*)out, "%d ", now->height);
#endif
    fprintf(this->out, "\n");
    _traversal(node->right);
}

int Avltree::_search(int key)
{
    Node* node = this->root;
    if (node == nullptr) return -1;

    while (node->key != key)
    {

        if (key <= node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }


        if (node == nullptr)
        {
            return -1;
        }
    }
#ifdef VERBOSE
    printf("check %d hgi : %d\n", _node->key, _node->height);
#endif
    return node->value;
}

Node* Avltree::_insert(Node* node, int key, int value)
{
    if (node == nullptr)
    {
        return new Node(key, value);
    }
    else if (node != nullptr)
    {
        if (key < node->key)
        {
            node->left = _insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = _insert(node->right, key, value);
        }
    }
    node->setHeight();
    int bf = node->getBalanceFactor();
    if (bf > 1)
    {
        if (key < node->left->key)
        {
            return node->rightRotate();
        }
        else if (key > node->left->key)
        {
            node->left = node->left->leftRotate();
            return node->rightRotate();
        }
    }
    if (bf < -1)
    {
        if (key > node->right->key)
        {
            return node->leftRotate();
        }
        else if (key < node->right->key) {
            node->right = node->right->rightRotate();
            return node->leftRotate();
        }
    }
    return node;
}



Node* Avltree::_delete(Node* node, int key)
{
    if (node == nullptr)
    {
        return NULL;
    }
    else if (key < node->key)
    {
        node->left = _delete(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = _delete(node->right, key);
    }
    else if (key == node->key)
    {
        if ((node->left == nullptr) || (node->right == nullptr))
        {
            Node* tmp = node->left ? node->left : node->right;
            if (node->left == nullptr && node->right == nullptr)
            {
                tmp = node;
                node = nullptr;
            }
            else
            {
                *node = *tmp;
            }
            this->count--;
            delete(tmp);
        }
        else {
            Node* temp = (node->right)->getMinNode();
            node->key = temp->key;
            node->value = temp->value;
            node->right = _delete(node->right, temp->key);
        }
    }
    if (node == NULL)
        return node;

    node->setHeight();
    int bf = node->getBalanceFactor();
    if (bf > 1)
    {
        if (node->left->getBalanceFactor() >= 0)
        {
            return node->rightRotate();
        }
        else
        {
            node->left = node->left->leftRotate();
            return node->rightRotate();
        }
    }
    if (bf < -1)
    {
        if (node->right->getBalanceFactor() <= 0)
        {
            return node->leftRotate();
        }
        else
        {
            node->right = node->right->rightRotate();
            return node->leftRotate();
        }
    }
    return node;
}