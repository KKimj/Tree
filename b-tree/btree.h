#ifndef BTREE_H
#define BTREE_H
#include <cstdio>
#include <cstdlib>


class Node {
public:
    int key, value, height;
    Node* left;
    Node* right;
    int bf;
    int bf_left;
    int bf_right;

    // btree node

    Node* parent;
    int* keys;
    int* values;
    Node ** pointers;
    bool isRoot, isLeaf;
    int numKeys;
    Node()
    {
        left = nullptr;
        right = nullptr;
        height = 1;
        key = 0;
        value = 0;
        bf = 0;
        bf_left = 0;
        bf_right = 0;
        isRoot = false, isLeaf = false;
        numKeys = 0;
        parent = nullptr;
        keys = nullptr;
        pointers = nullptr;
        values = nullptr;
    }
    Node(int _key, int _value)
    {
        left = nullptr;
        right = nullptr;
        height = 1;
        key = _key;
        value = _value;
        bf = 0;
        bf_left = 0;
        bf_right = 0;
        isRoot = false, isLeaf = false;
        numKeys = 0;
        parent = nullptr;
        keys = nullptr;
        pointers = nullptr;
        values = nullptr;
    }
    Node(int order, bool _isLeaf)
    {
        this->keys = new int[order - 1]();
        this->values = new int[order - 1]();
        this->pointers = (Node **)malloc(sizeof(Node *) * order);
        this->pointers[0] = NULL;

        this->numKeys = 0;
        this->parent = NULL;

        this->isLeaf = _isLeaf;
        this->isRoot = false;

        left = nullptr;
        right = nullptr;
        height = 1;
        key = 0;
        value = 0;
        bf = 0;
        bf_left = 0;
        bf_right = 0;
    }

    // Record를 할당 받는 Node는 항상 Leaf이다.
    Node(int _key, int _value, int order, bool _isLeaf)
    {
        this->keys = new int[order - 1]();
        this->values = new int[order - 1]();
        this->pointers = (Node**)malloc(sizeof(Node*) * order);


        this->numKeys = 1;
        this->parent = NULL;

        this->isRoot = false;
        this->isLeaf = _isLeaf;


        this->keys[0] = _key;
        //this->pointers[0] = new Record(_key, _value);
        


        left = nullptr;
        right = nullptr;
        height = 1;
        key = _key;
        value = _value;
        bf = 0;
        bf_left = 0;
        bf_right = 0;
    }

    Node* AddRecord(int _key, int _value, Node * pointer, bool isLeaf ,int order)
    {
        
        {
            int target = 0, i;
            while (target < this->numKeys && this->keys[target] < _key)
            {
                target++;
            }
            for (i = this->numKeys; i > target; i--)
            {
                this->keys[i] = this->keys[i - 1];
                this->values[i] = this->values[i - 1];
                this->pointers[i] = this->pointers[i - 1];
            }
            this->keys[target] = _key;
            this->values[target] = _value;
            this->pointers[target+1] = pointer;
            this->numKeys++;
            this->pointers[this->numKeys] = NULL;
            
        }
        if(!(this->numKeys < order))
        {
            Node* tmp = new Node(order, false);
            Node* right = new Node(order, isLeaf);

            this->parent = tmp;
            right->parent = tmp;

            //TODO
            tmp->keys[0] = this->keys[(order - 1) / 2];
            tmp->values[0] = this->values[(order - 1) / 2];
            this->keys[(order - 1) / 2] = 0;
            this->values[(order - 1) / 2] = 0;
            tmp->numKeys = 1;
            tmp->pointers[0] = this;
            tmp->pointers[1] = right;


            right->numKeys = this->numKeys - (order - 1) / 2;
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

    Node* AddNode(Node * node)
    {
        if (node == nullptr)
        {
            return NULL;
        }

        int target = 0, i;
        while (target < this->numKeys && this->keys[target] < node->keys[0])
        {
            target++;
        }
        for (i = this->numKeys; i > target; i--)
        {
            this->keys[i] = this->keys[i - 1];
            this->values[i] = this->values[i - 1];
            this->pointers[i] = this->pointers[i - 1];
        }
        /*this->keys[target] = _key;
        this->values[target] = _value;
        this->pointers[target] = pointer;
        this->numKeys++;*/
        this->pointers[this->numKeys] = NULL;
        return this;
    }

    Node* rightRotate()
    {
        Node* tmp = this->left;
        Node* tmp2 = tmp->right;
        tmp->right = this;
        this->left = tmp2;
        tmp->getHeight();
        this->getHeight();
        return tmp;

        /*Node * tmp = this->left;
        this->left = tmp->right;
        tmp->right = this;

        tmp->setHeight();

        return tmp;*/

    }
    Node* leftRotate()
    {
        Node* tmp = this->right;
        Node* tmp2 = tmp->left;
        tmp->left = this;
        this->right = tmp2;
        this->getHeight();
        tmp->getHeight();
        return tmp;

        /*
        Node* tmp = this->right;
        this->right = tmp->left;
        tmp->left = this;
        tmp->setHeight();
        return tmp;*/

    }

    int setHeight()
    {
        this->getHeight();
        if (this->left != nullptr)
        {
            this->left->getHeight();
        }
        if (this->right != nullptr)
        {
            this->right->getHeight();
        }
        return this->height;
    }
    int getHeight()
    {
        if (this == nullptr)
        {
            return 0;
        }
        int _left = 0, _right = 0;
        if (this->left != nullptr)
        {
            _left = this->left->height;
        }
        if (this->right != nullptr)
        {
            _right = this->right->height;
        }
        this->height = _left;
        if (this->height < _right) {
            this->height = _right;
        }
        this->height += 1;
        return this->height;
    }
    int getBalanceFactor()
    {
        int _left = 0, _right = 0;
        if (this == nullptr)
        {
            return 0;
        }

        if (this->left != nullptr)
        {
            _left = this->left->getHeight();
        }
        if (this->right != nullptr)
        {
            _right = this->right->getHeight();
        }
        this->bf = _left - _right;
        return this->bf;
    }
    Node* getMinNode()
    {
        Node* now = this;
        while (now->left != NULL)
            now = now->left;
        return now;
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
    Node* _getLeafNode(int _key)
    {
        Node* now = this->root;
        int target;
        while (now->isLeaf != true)
        {
            target = 0;
            while (target < now->numKeys && now->keys[target] < _key)
            {
                target++;
            }
            now = now->pointers[target];
        }
        return now;
    }
};

#endif