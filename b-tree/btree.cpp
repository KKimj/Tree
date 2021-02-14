#include "btree.h"
#include <cstdio>
#include <cstdlib>


#define VERBOSE

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
        this->root = this->root->AddRecord(key, value, NULL, NULL ,true, this->order);
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
        fprintf(this->out, "%d ", i);
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
        node = node->AddRecord(key, value, NULL, NULL,node->isLeaf ,this->order);
        if (node->isLeaf == false)
        {
            if (node->parent == nullptr)
            {
                return node;
            }
        }
        else
        {
            return node;
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
        Node * tmp = _Insert(node->pointers[target], key, value);
        if (tmp->isLeaf == false && node->pointers[target]->isLeaf == true)
        {
            tmp->parent = node->parent;
            node = node->AddNode(tmp, this->order);
        }
        else if (node != tmp->parent && tmp->parent == node->parent)
        {
            tmp->parent = node->parent;
            node = node->AddNode(tmp, this->order);
        }
        else
        {
            tmp->parent = node;
            node->pointers[target] = tmp;
        }
    }
    return node;
}



Node* Btree::_Delete(Node* node, int key)
{
    if (node == nullptr)
    {
        return NULL;
    }
    
    return node;
}