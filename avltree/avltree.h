#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdio>


class Node {
public:
    int key, value, height;
    Node* left;
    Node* right;
    int bf;
    int bf_left;
    int bf_right;
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
    }

    Node* RightRotate()
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
    Node* LeftRotate()
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


class Avltree
{
public:
    Node* root;
    int count;

    FILE* out;

    int Insert(int value);
    int Search(int key);
    void Delete(int key);
    void Print(char* filepath);




    Avltree()
    {
        root = nullptr;
        count = 0;
        out = nullptr;
    }
private:
    void _Traversal(Node* node);
    int _Search(int key);
    Node* _Insert(Node* node, int key, int value);
    Node* _Delete(Node* node, int key);
};

#endif