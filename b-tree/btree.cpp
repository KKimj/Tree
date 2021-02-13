#include "btree.h"
#include <cstdio>
#include <cstdlib>



void Btree::print(char* filepath)
{
    this->out = fopen(filepath, "w");
    _traversal(this->root);
    fclose(this->out);
}

int Btree::insert(int key, int value)
{
    if (_search(key) != NULL)
    {
        return key;
    }

    if (this->count == 0 || this->root == nullptr)
    {
        this->root = new Node(this->order, true);
        this->root = this->root->addRecord(key, value, NULL, true, this->order);
        this->count = 1;
        this->root->isRoot = true;
        return key;
    }
    else
    {
        this->root = this->_insert(this->root, key, value);
        return key;
    }
    return key;
}
int Btree::search(int key)
{
    int tmp = this->_search(key);
    if (tmp == NULL)
    {
        return NULL;
    }
    return tmp;
}
void Btree::deleteNode(int key)
{
    this->root = _delete(this->root, key);
}



void Btree::_traversal(Node* node)
{
    if (node == nullptr) return;

    
    
    int i;
    for (i = 0; i < node->numKeys; i++)
    {
        fprintf(this->out, "%d ", node->keys[i]);
        fprintf(this->out, "%d ", node->values[i]);
#ifdef VERBOSE
        fprintf((FILE*)out, "%d ", now->height);
#endif
        fprintf(this->out, "\n");
        _traversal(node->pointers[i]);
    }
    _traversal(node->pointers[i]);
}

int Btree::_search(int key)
{
    Node* node = this->root;
    if (node == nullptr) return NULL;
    int i;

    while (node != nullptr)
    {
        for (i = 0; i < node->numKeys; i++)
        {
            if (key >= node->keys[i])
            {
                if (key == node->keys[i])
                {
                    return node->values[i];
                }
                continue;
            }

            break;
        }
        /*if (i >= node->numKeys)
        {
            return NULL;
        }*/
        node = (Node*)node->pointers[i];
    }
    if (node == nullptr) return NULL;
    if (node->keys[i] == key || i == node->numKeys)
    {
        return node->values[i];
    }
    return NULL;
}

Node* Btree::_insert(Node* node, int key, int value)
{
    if (node->isLeaf == true)
    {
        node = node->addRecord(key, value, NULL, node->isLeaf ,this->order);
        //node = node->addRecord(key, value, node->parent, this->order);
        if (node->isLeaf == false)
        {
            if (node->parent == nullptr)
            {
                return node;
            }
            // split이 일어남
            // node = node->addNode();
        }
    }
    else
    {
        int target;
        target = 0;
        while (target < node->numKeys && node->keys[target] < key)
        {
            target++;
        }
        node = _insert(node->pointers[target], key, value);
    }
    return node;
}



Node* Btree::_delete(Node* node, int key)
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