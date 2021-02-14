#include "avltree.h"
#include <cstdio>
#include <cstdlib>



void Avltree::Print(char* filepath)
{
    this->out = fopen(filepath, "w");
    _Traversal(this->root);
    fclose(this->out);
}

int Avltree::Insert(int value)
{
    this->root = _Insert(this->root, value, value);
    this->count++;
    return value;
}
int Avltree::Search(int key)
{
    return this->_Search(key);
}
void Avltree::Delete(int key)
{
    this->root = _Delete(this->root, key);
}



void Avltree::_Traversal(Node* node)
{
    if (node == nullptr) return;

    _Traversal(node->left);
    fprintf(this->out, "%d ", node->value);
#ifdef VERBOSE
    fprintf((FILE*)out, "%d ", now->height);
#endif
    fprintf(this->out, "\n");
    _Traversal(node->right);
}

int Avltree::_Search(int key)
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

Node* Avltree::_Insert(Node* node, int key, int value)
{
    if (node == nullptr)
    {
        return new Node(key, value);
    }
    else if (node != nullptr)
    {
        if (key < node->key)
        {
            node->left = _Insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = _Insert(node->right, key, value);
        }
    }
    node->setHeight();
    int bf = node->getBalanceFactor();
    if (bf > 1)
    {
        if (key < node->left->key)
        {
            return node->RightRotate();
        }
        else if (key > node->left->key)
        {
            node->left = node->left->LeftRotate();
            return node->RightRotate();
        }
    }
    if (bf < -1)
    {
        if (key > node->right->key)
        {
            return node->LeftRotate();
        }
        else if (key < node->right->key) {
            node->right = node->right->RightRotate();
            return node->LeftRotate();
        }
    }
    return node;
}



Node* Avltree::_Delete(Node* node, int key)
{
    if (node == nullptr)
    {
        return NULL;
    }
    else if (key < node->key)
    {
        node->left = _Delete(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = _Delete(node->right, key);
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
            node->right = _Delete(node->right, temp->key);
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
            return node->RightRotate();
        }
        else
        {
            node->left = node->left->LeftRotate();
            return node->RightRotate();
        }
    }
    if (bf < -1)
    {
        if (node->right->getBalanceFactor() <= 0)
        {
            return node->LeftRotate();
        }
        else
        {
            node->right = node->right->RightRotate();
            return node->LeftRotate();
        }
    }
    return node;
}