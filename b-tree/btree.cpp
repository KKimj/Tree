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
        this->count++;
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
    if (this->root == nullptr)
    {
        return;
    }
    if (this->root->numKeys == 0)
    {
        Node* tmp = this->root->pointers[0];
        free(this->root);
        this->root = NULL;
        this->root = tmp;
    }
}



void Btree::_Traversal(Node* node)
{
    if (node == nullptr) return;

    
    
    int i;
    for (i = 0; i < node->numKeys; i++)
    {
        fprintf(this->out, "%d\t", node->keys[i]);
        fprintf(this->out, "%d\t", node->values[i]);
#ifdef VERBOSE
        fprintf(this->out, "%d\t", i);
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
    int target;
    target = 0;
    int t = (this->order + 1) / 2;
    while (target < node->numKeys && node->keys[target] < key)
    {
        target++;
    }
    if (node->keys[target] == key)
    {
        if (node->isLeaf == true)
        {
            node->DeleteRecord(node->keys[target]);
            this->count--;
            return node;
        }
        // node->isLeaf == false
        else
        {
            int left_child_num = 0;
            int right_child_num = 0;

            if(node->pointers[target] != nullptr)
                left_child_num = node->pointers[target]->numKeys;
            if (node->pointers[target+1] != nullptr)
                right_child_num = node->pointers[target + 1]->numKeys;

            Node* borrow;
            
            if (left_child_num >= t && node->pointers[target]!=nullptr)
            {
                // left child borrow
                borrow = node->pointers[target];
                while (borrow != nullptr && !borrow->isLeaf)
                {
                    borrow = borrow->pointers[borrow->numKeys];
                }
                if (borrow != nullptr && borrow->isLeaf)
                {
                    node->keys[target] = borrow->keys[borrow->numKeys - 1];
                    node->values[target] = borrow->values[borrow->numKeys - 1];

                    borrow->keys[borrow->numKeys - 1] = key;
                    _Delete(node->pointers[target], key);
                    //node = _Delete(node->pointers[target], key);
                }
            }
            //else if (right_child_num >= t && node->pointers[target+1] != nullptr)
            else
            {
                // right child borrow
                borrow = node->pointers[target+1];
                while (borrow != nullptr && !borrow->isLeaf)
                {
                    borrow = borrow->pointers[0];
                }
                if (borrow != nullptr && borrow->isLeaf)
                {
                    node->keys[target] = borrow->keys[0];
                    node->values[target] = borrow->values[0];

                    borrow->keys[0] = key;
                    _Delete(node->pointers[target + 1], key);
                    //node = _Delete(node->pointers[target + 1], key);
                }
            }
        }
    }
    else
    {
        _Delete(node->pointers[target], key);
        //node = _Delete(node->pointers[target], key);
        if (node->pointers[0] != nullptr && node->numKeys == 0)
        {
            node = node->Merge(0);
        }
        /*else if (node->pointers[0] != nullptr && node->numKeys <= 1 && node->pointers[0]->numKeys<this->order)
        {
            node = node->Merge(0);
        }*/
        else if (target < node->numKeys && node->pointers[target] != nullptr && node->pointers[target + 1] != nullptr && (node->pointers[target]->numKeys + node->pointers[target + 1]->numKeys <this->order))
        {
            // target , target + 1
            node = node->Merge(target);
        }
        else if (target > 0 && node->pointers[target - 1] != nullptr && node->pointers[target] != nullptr && (node->pointers[target - 1]->numKeys + node->pointers[target]->numKeys < this->order))
        {
            // target - 1, target
            node = node->Merge(target - 1);
        }
    }

    // merge
    
    return node;
}