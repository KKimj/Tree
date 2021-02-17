#ifndef BTREE_H
#define BTREE_H
#include <cstdio>
#include <cstdlib>


class Node {
public:
    
    // btree node
    Node* parent;
    int* keys;
    int* values;
    Node ** pointers;
    bool isRoot, isLeaf;
    int numKeys;
    
    Node(int order, bool _isLeaf)
    {
        this->keys = new int[order]();
        this->values = new int[order]();
        this->pointers = (Node **)malloc(sizeof(Node *) * (order+1));
        
        this->pointers[0] = NULL;
        this->pointers[order-1] = NULL;

        this->numKeys = 0;
        this->parent = NULL;

        this->isLeaf = _isLeaf;
        this->isRoot = false;

    }

    
    Node* AddRecord(int key, int value, Node * leftPointer, Node* rightPointer, bool isLeaf ,int order)
    {
        {
            int target = 0, i;
            while (target < this->numKeys && this->keys[target] < key)
            {
                target++;
            }

            this->pointers[numKeys+1] = this->pointers[numKeys];
            for (i = this->numKeys; i > target; i--)
            {
                this->keys[i] = this->keys[i - 1];
                this->values[i] = this->values[i - 1];
                this->pointers[i] = this->pointers[i - 1];
            }
            this->keys[target] = key;
            this->values[target] = value;
            this->pointers[target] = leftPointer;
            this->pointers[target+1] = rightPointer;
            this->numKeys++;
        }
        if(!(this->numKeys < order))
        {
            Node* tmp = new Node(order, false);
            Node* right = new Node(order, isLeaf);

            tmp->parent = NULL;
            if (this->parent != nullptr)
            {
                tmp->parent = this->parent->parent;
            }

            this->parent = tmp;
            right->parent = tmp;

            tmp->keys[0] = this->keys[(order - 1) / 2];
            tmp->values[0] = this->values[(order - 1) / 2];
            this->keys[(order - 1) / 2] = 0;
            this->values[(order - 1) / 2] = 0;
            tmp->numKeys = 1;
            tmp->pointers[0] = this;
            tmp->pointers[1] = right;


            right->numKeys = this->numKeys - (order - 1) / 2 - 1;
            for (int i = 0; i < right->numKeys; i++)
            {
                right->keys[i] = this->keys[(order - 1) / 2 + 1 + i];
                right->values[i] = this->values[(order - 1) / 2 + 1 + i];
                right->pointers[i] = this->pointers[(order - 1) / 2 + 1 + i];

                this->keys[(order - 1) / 2 + 1 + i] = 0;
                this->values[(order - 1) / 2 + 1 + i] = 0;
                this->pointers[(order - 1) / 2 + 1 + i] = NULL;
            }
            right->pointers[right->numKeys] = this->pointers[this->numKeys];

            this->numKeys = (order - 1) / 2;
            return tmp;
        }
        return this;
    }

    Node* AddNode(Node * node, int order)
    {
        return this->AddRecord(node->keys[0], node->values[0], node->pointers[0], node->pointers[1], this->isLeaf, order);
    }

    Node* DeleteRecord(int key)
    {
        int target = 0, i;
        while (target < this->numKeys && this->keys[target] < key)
        {
            target++;
        }
        if (this->keys[target] != key)
        {
            return this;
        }
        
        for (i = target; i < this->numKeys; i++)
        {
            this->keys[i] = this->keys[i + 1];
            this->values[i] = this->values[i + 1];
            this->pointers[i] = this->pointers[i + 1];
        }
        this->pointers[this->numKeys] = NULL;
        this->numKeys--;
        this->keys[this->numKeys] = 0;
        this->values[this->numKeys] = 0;
        return this;
    }

    Node* Merge(int target)
    {
        int i;
        
        Node* left = this->pointers[target];
        Node* right = this->pointers[target + 1];
        left->keys[left->numKeys] = this->keys[target];
        left->numKeys++;

        // right child
        i = 0;
        while (right->numKeys != 0)
        {
            left->keys[left->numKeys] = right->keys[i];
            left->values[left->numKeys] = right->values[i];
            left->pointers[left->numKeys] = right->pointers[i];
            i++;
            left->numKeys++;
            right->numKeys--;
        }
        left->pointers[left->numKeys] = right->pointers[i];

        
        delete(this->pointers[target + 1]);
        this->pointers[target + 1] = NULL;
        right = NULL;

        this->pointers[target + 1] = left;
        
        for (i = target; i < this->numKeys; i++)
        {
            this->keys[i] = this->keys[i + 1];
            this->values[i] = this->values[i + 1];
            this->pointers[i] = this->pointers[i + 1];
        }
        this->pointers[target] = left;
        this->numKeys--;
        return this;
    }
};


class Btree
{
public:
    Node* root;
    int order;
    int count;


    FILE* out;

    int Insert(int key, int value);
    int Search(int key);
    void Delete(int key);
    void Print(char* filepath);




    Btree(int _order)
    {
        this->root = nullptr;
        this->count = 0;
        this->out = nullptr;
        this->order = _order;
    }
private:
    void _Traversal(Node* node);
    int _Search(int key);
    Node* _Insert(Node* node, int key, int value);
    Node* _Delete(Node* node, int key);
    Node* _getLeafNode(int key)
    {
        Node* now = this->root;
        int target;
        while (now->isLeaf != true)
        {
            target = 0;
            while (target < now->numKeys && now->keys[target] < key)
            {
                target++;
            }
            now = now->pointers[target];
        }
        return now;
    }
};

#endif