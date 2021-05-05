#include "Tree.h"


Tree::~Tree()
{
    if (nullptr != _root)
    {
        deleteNode(_root);
    }
}


Tree::Tree(const Tree &rhs)
    : _root(nullptr)
{
    _root = clone(rhs._root);
}


Tree::Tree(Tree &&rhs)
    : _root(rhs._root)
{
    rhs._root = nullptr;
}


Tree & Tree::operator=(const Tree &rhs)
{
    if (this != &rhs)
    {
        if (nullptr != _root)
        {
            deleteNode(_root);
        }

        _root = clone(rhs._root);
    }

    return *this;
}


Tree & Tree::operator=(Tree &&rhs)
{
    std::swap(_root, rhs._root);
    return *this;
}


Node * Tree::setRootLabel(const QString &rootLabel)
{
    if (nullptr == _root)
    {
        _root = new Node(rootLabel);
    }
    else
    {
        _root->_label = rootLabel;
    }

    return _root;
}


Node * Tree::clone(Node *node)
{
    if (nullptr == node)
    {
        return nullptr;
    }

    Node * leftChild = clone(node->_leftChild);
    Node * rightChild = clone(node->_rightChild);
    Node * newNode = new Node(node->_label);
    newNode->_leftChild = leftChild;
    newNode->_rightChild = rightChild;
    return newNode;
}


void Tree::deleteNode(Node *node)
{
    if (nullptr == node)
    {
        return;
    }

    deleteNode(node->_leftChild);
    deleteNode(node->_rightChild);
    delete node;
}
