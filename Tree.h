#pragma once

#include <QString>


class Node
{
public:
    Node(const QString &label = QString())
        : _label(label)
        , _leftChild(nullptr)
        , _rightChild(nullptr)
    {}

    QString _label;
    Node *_leftChild;
    Node *_rightChild;
};


class Tree
{
public:
    Tree() : _root(nullptr)
    {}

    Tree(const QString &label) : _root(nullptr)
    {
        _root = new Node(label);
    }

    Tree(Node *node) : _root(node)
    {}

    ~Tree();
    Tree(const Tree &rhs);
    Tree(Tree &&rhs);
    Tree & operator=(const Tree &rhs);
    Tree & operator=(Tree &&rhs);

    Node * getRoot() const { return _root; }
    Node * setRootLabel(const QString &rootLabel);
    static Node * getLeftChild(const Node *node) { return node->_leftChild; }
    static Node * getRightChild(const Node *node) { return node->_rightChild; }
    static void setLeftChild(Node *parent, Node *leftChild) { parent->_leftChild = leftChild; }
    static void setRightChild(Node *parent, Node *rightChild) { parent->_rightChild = rightChild; }

    static Node * clone(Node *node);
    void deleteNode(Node *node);

    Node *_root;
};
