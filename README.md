# Tree

Develop Status
- [x] AVL tree
- [x] B-tree

## Getting Started
```
$ git clone https://github.com/KKimj/Tree
```

### Prerequisites
```
$ sudo apt update && sudo apt upgrade
$ sudo apt install g++
```

## Running the tests

### [B-tree](b-tree/readme.md)


## Tip
```c++
Avltree avltree;

int key;
int value;

avltree.Insert(key, value);
avltree.Search(key);
avltree.Delete(key);

```

```c++
Btree * btree;

int order = 200;
btree = new Btree(order);

int key;
int value;

btree->Insert(key, value);
btree->Search(key);
btree->Delete(key);

```

## Acknowledgments
https://www.cs.usfca.edu/~galles/visualization/BTree.html
