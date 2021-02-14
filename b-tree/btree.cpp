#include "btree.h"
#include <cstdio>
#include <cstdlib>



void Btree::Print(char* filepath)
{
    this->out = fopen(filepath, "w");
    _Traversal(this->root);
    fclose(this->out);
}

int Btree::Insert(int key, int value)
{
    if (_Search(key) != NULL)
    {
        return key;
    }

    if (this->count == 0 || this->root == nullptr)
    {
        this->root = new Node(this->order, true);
        this->root = this->root->AddRecord(key, value, NULL, true, this->order);
        this->count = 1;
        this->root->isRoot = true;
        return key;
    }
    else
    {
        this->root = this->_Insert(this->root, key, value);
        return key;
    }
    return key;
}
int Btree::Search(int key)
{
    int tmp = this->_Search(key);
    if (tmp == NULL)
    {
        return NULL;
    }
    return tmp;
}
void Btree::Delete(int key)
{
    this->root = _Delete(this->root, key);
}



void Btree::_Traversal(Node* node)
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
        _Traversal(node->pointers[i]);
    }
    _Traversal(node->pointers[i]);
}

int Btree::_Search(int key)
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

Node* Btree::_Insert(Node* node, int key, int value)
{
    if (node->isLeaf == true)
    {
        node = node->AddRecord(key, value, NULL, node->isLeaf ,this->order);
        //node = node->AddRecord(key, value, node->parent, this->order);
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
        node = _Insert(node->pointers[target], key, value);
    }
    return node;
}



Node* Btree::_Delete(Node* node, int key)
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