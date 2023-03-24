#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    bool isBalanced(Node<Key,Value> *start) const;
    int getHeight(Node<Key,Value> *root) const;
    void leftRotate(Node<Key,Value> *root);
    void rightRotate(Node<Key,Value> *root);
    void fixRotation(Node<Key,Value> *curr);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    BinarySearchTree<Key,Value>::insert(new_item);
    if(!BinarySearchTree<Key,Value>::isBalanced()){
        fixRotation(BinarySearchTree<Key,Value>::internalFind(new_item.first));
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    Node<Key,Value> *start = BinarySearchTree<Key,Value>::internalFind(key)->getParent();
    BinarySearchTree<Key,Value>::remove(key);
    if(!BinarySearchTree<Key,Value>::isBalanced()){fixRotation(start);}
}

template<class Key, class Value>
void AVLTree<Key, Value>::fixRotation(Node<Key,Value> *start){
    Node<Key,Value> * grandchild = start;
    Node<Key,Value> * child = grandchild->getParent();
    Node<Key,Value> * curr = child->getParent();
    while(isBalanced(curr)){
        grandchild = child;
        child = curr;
        curr = curr->getParent();
    }
    if(child = curr->getLeft()){
        if(grandchild = child->getRight()){
            leftRotate(child);
        }
        rightRotate(curr);
    }else{
        if(grandchild = child->getLeft()){
            rightRotate(child);
        }
        leftRotate(curr);
    }
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::isBalanced(Node<Key,Value> *start) const
{
	if(abs(getHeight(start->getLeft()) - getHeight(start->getRight())) > 1){return false;}
	if(start->getLeft() != nullptr){
		if(!isBalanced(start->getLeft())){return false;}
	}
	if(start->getRight() != nullptr){
		if(!isBalanced(start->getRight())){return false;}
	}
	return true;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::getHeight(Node<Key,Value> *root) const{
	if(root == nullptr){return 0;}
	int left = getHeight(root->getLeft());
	int right = getHeight(root->getRight());
	return std::max(left, right) + 1;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::leftRotate(Node<Key,Value> *root){
    Node<Key, Value> * parent = root->getParent();
    Node<Key, Value> * right = root->getRight();
    if(parent != NULL){
        if(root == parent->getLeft()){
            parent->setLeft(right);
        }else{
            parent->setRight(right);
        }
        right->setParent(parent);
    }else{
        right->setParent(NULL);
    }
    root->setRight(right->getLeft());
    right->getLeft()->setParent(root);
    right->setLeft(root);
    root->setParent(right);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rightRotate(Node<Key,Value> *root){
    Node<Key, Value> * parent = root->getParent();
    Node<Key, Value> * left = root->getLeft();
    if(parent != NULL){
        if(root == parent->getLeft()){
            parent->setLeft(left);
        }else{
            parent->setRight(left);
        }
        left->setParent(parent);
    }else{
        left->setParent(NULL);
    }
    root->setLeft(left->getRight());
    left->getRight()->setParent(root);
    left->setRight(root);
    root->setParent(left);
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
