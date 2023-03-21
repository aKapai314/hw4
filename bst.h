#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath> 

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
using namespace std;

template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
		static Node<Key, Value>* successor(Node<Key, Value>* current);
    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap(Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		virtual void clearHelper(Node<Key, Value>* n);
		int getPathLength(Node<Key, Value>* n) const;
		bool isBalancedHelper(Node<Key, Value>* n) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return (rhs.current_ == current_);
  /*  // TODO
		if(rhs.current_ == NULL){
			return (current_ == NULL);
		}
		return (current_->getValue() == (rhs.current_)->getValue());
		*/
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{

	return (rhs.current_ != current_);
   /*
		if(rhs.current_ == NULL){
			return !(current_ == NULL);
		}
		return !(current_->getKey() == (rhs.current_)->getValue());
		*/
		
}


/**
* Advances the iterator's location using an in-order sequencing
*/

//YOU NEED TO REWRITE THIS AND CONSIDER ALL POSSIBILITIES
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		current_ = successor(current_);
		/*
    Node<Key, Value>* next = current_;
    
		if(next == NULL)
		{
			current_ = NULL;
		}
		else if(next->getRight() != NULL)
		{
			next = next->getRight();
			while(next->getLeft() != NULL)
				next = next->getLeft();
			current_ = next;
			return *this; 
		}
		while(next->getParent() != NULL && next->getParent()->getRight() == next)
			next = next->getParent();

		current_ = next->getParent();
		*/
		return *this;
		/*
    if(current_ != NULL)
    {
        if(next->getRight() != NULL)
        {
            next = next->getRight();
            while(next->getLeft() != NULL){
                next = next->getLeft();
						}
            current_ = next;   
        }
        else if(next->getParent() != NULL)
        {
            next = next->getParent();
            while(next->getParent() != NULL)
            {
                if(next->getParent()->getLeft() == next)
                {
                    current_ = next->getParent();
                    break;
                }
                next = next->getParent();
            }
						if(current_->getParent() == next)
							current_ = NULL;
        }

    }
		return *this;
		*/

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
  root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	Key key = keyValuePair.first;
  Node<Key, Value>* next = internalFind(key);
	if(next != NULL)
		next->setValue(keyValuePair.second);
	else
	{
		//dynamically allocate a new Node with inputted key/value
		Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		//cout << "adding key " << key << endl;
		if(root_ == NULL){
			root_ = newNode;
		}
		else{
			//start at the top of the tree
			next = root_;
			while(next != NULL)
			{
				if(key > next->getKey()) //go to the right
				{
					//cout << "at node " << next->getKey() << ", going right" << endl;
					if(next->getRight() == NULL) //if there's an empty spot
					{
						newNode->setParent(next);
						next->setRight(newNode);
						break;
					}
					next = next->getRight();
				}
				else //go to the left
				{
					//cout << "at node " << next->getKey() << ", going left" << endl;
					if(next->getLeft() == NULL) //if there's an empty spot
					{
						//cout << "theres an empty spot" << endl;
						newNode->setParent(next);
						next->setLeft(newNode);
						break;
					}
					next = next->getLeft();
				}
			}
		}
	}
	//cout << "done" << endl;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{

    Node<Key, Value>* rmvNode = internalFind(key);

		if(rmvNode == NULL)
			return;

		if(rmvNode->getLeft() != NULL && rmvNode->getRight() != NULL) //if node has both children
		{
			Node<Key, Value>* pred = predecessor(rmvNode);
			nodeSwap(pred, rmvNode);
			if(root_ == rmvNode)
				root_ = pred;
		}

		if(rmvNode->getLeft() == NULL && rmvNode->getRight() == NULL) //if node has no children
		{
			if(rmvNode == root_) //if node has no parent
				root_ = NULL;
			else if(rmvNode->getParent()->getLeft() == rmvNode) //if node is a left child
				rmvNode->getParent()->setLeft(NULL);
			else //if node is a right child
				rmvNode->getParent()->setRight(NULL);
		}
		else if(rmvNode->getLeft() == NULL) //if node has only a right child
		{
			Node<Key, Value>* rChild = rmvNode->getRight();
			
//IFTHENODE BECOMESt the root you NEED to set its parent to null
			if(rmvNode == root_){ //if node has no parent
				root_ = rChild;
				rChild->setParent(NULL);
			}
			else if(rmvNode->getParent()->getLeft() == rmvNode){//if node is a left child
				rmvNode->getParent()->setLeft(rChild);
				rChild->setParent(rmvNode->getParent());
			}
			else{
				rmvNode->getParent()->setRight(rChild); //if node is a right child 
				rChild->setParent(rmvNode->getParent());
			}
		}
		else //if node has only a left child
		{
			Node<Key, Value>* lChild = rmvNode->getLeft();

			if(rmvNode == root_){ //if node has no parent
				root_ = lChild;
				lChild->setParent(NULL);
			}
			else if(rmvNode->getParent()->getLeft() == rmvNode){ //if node is a left child
				rmvNode->getParent()->setLeft(lChild);
				lChild->setParent(rmvNode->getParent());
			}
			else{
				rmvNode->getParent()->setRight(lChild); //if node is a right child 
				lChild->setParent(rmvNode->getParent());
			}
		}
	

		delete rmvNode;
}


/*
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateParent(Node<Key, Value>* n)
{
	if(n->getParent() == NULL)
		return;
	
	Node<Key, Value>* p = n->getParent();

	if(p->getLeft() == n){
		p->setLeft(NULL);
	}
	else if(p->getRight() == n){
		p->setRight(NULL);
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(Node<Key, Value>* rmvNode)
{
		if(rmvNode == NULL)
		{
			cout << "node is null" << endl;
			return;

		}
		else if(rmvNode->getLeft() == NULL && rmvNode->getRight() == NULL)
		{
			cout << "node has no children" << endl;
			if(rmvNode == root_)
				root_ = NULL;
			else
				updateParent(rmvNode);
		
			delete rmvNode;
		}	
		else if(rmvNode->getLeft() == NULL) //promote right child
		{
			cout << "node has only right child" << endl;

			Node<Key, Value>* rChild = rmvNode->getRight();
			Node<Key, Value>* parent = rmvNode->getParent();

			if(rmvNode == root_)
				root_ = rChild;
			else
				updateParent(rmvNode);

			delete rmvNode;

			rChild->setParent(parent);
		}
		else if(rmvNode->getRight() == NULL) //promote left child
		{
			cout << "node has only left child" << endl;

			Node<Key, Value>* lChild = rmvNode->getLeft();
			Node<Key, Value>* parent = rmvNode->getParent();

			if(rmvNode == root_)
				root_ = lChild;
			else
				updateParent(rmvNode);

			delete rmvNode;

			lChild->setParent(parent);	
		}
		else //swap with predecessor and remove
		{
			cout << "node has both children" << endl;
			cout << "predecessor is " << predecessor(rmvNode)->getKey() << endl;
			nodeSwap(predecessor(rmvNode), rmvNode);
			cout << "root is now " << root_->getKey() << endl;
			cout << "node to remove is now " << rmvNode->getKey() << endl;
			removeHelper(rmvNode);
		}
}

*/
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
	Node<Key, Value>* next = current;
    
    if(next != NULL)
    {
        if(next->getRight() != NULL)
        {
            next = next->getRight();
            while(next->getLeft() != NULL){
                next = next->getLeft();
						}
            return next;   
        }
        else if(next->getParent() != NULL)
        {
            next = next->getParent();
            while(next->getParent() != NULL)
            {
                if(next->getParent()->getLeft() == next)
                {
                    return next->getParent();
                    break;
                }
                next = next->getParent();
            }
						if(current->getParent() == next)
							return NULL;
        }
			}
			return NULL;
}




template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
  // TODO
    Node<Key, Value>* next = current;
    
    if(next != NULL)
    {
        if(next->getLeft() != NULL)
        {
            next = next->getLeft();
            while(next->getRight() != NULL){
                next = next->getRight();
						}
            return next;   
        }
        else if(next->getParent() != NULL)
        {
            next = next->getParent();
            while(next->getParent() != NULL)
            {
                if(next->getParent()->getRight() == next)
                {
                    return next->getParent();
                    break;
                }
                next = next->getParent();
            }
						if(current->getParent() == next)
							return NULL;
        }
			}
			return NULL;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
		clearHelper(root_);
		root_ = NULL;
		
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* n)
{
		if(n == NULL) //we are done
		{
				return;
		}

		Node<Key, Value>* rightSubtree = n->getRight();
		Node<Key, Value>* leftSubtree = n->getLeft();

		delete n;

		clearHelper(rightSubtree);
		clearHelper(leftSubtree);

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    Node<Key, Value>* next = root_;

		if(root_ == NULL)
			return NULL;

		while(next->getLeft() != NULL)
		{
			next = next->getLeft();
		}
		return next; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* next = root_;

    while(next != NULL)
    {
      if(next->getKey() == key)
        return next;
      else if(key > next->getKey())
        next = next->getRight();
			else
				next = next->getLeft(); 
    }

		return next;
    
}

/**
 * Return true iff the BST is balanced.
 */


template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return isBalancedHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* n) const
{
	//cout << "node has value " << n->getValue() << endl;
	if(n == NULL)
		return true;
	if( (n->getRight() == NULL) && (n->getLeft() == NULL) )
    return true;
	else if(isBalancedHelper(n->getRight()) && isBalancedHelper(n->getLeft()))
  {
  	int rightHeight = 0;
		int leftHeight = 0;

		if(n->getRight() != NULL)
			rightHeight = 1 + getPathLength(n->getRight());
		if(n->getLeft() != NULL)
			leftHeight = 1 + getPathLength(n->getLeft());
    if(abs(rightHeight - leftHeight) <= 1)
        return true;
  }
  return false;

}
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getPathLength(Node<Key, Value>* n) const 
{
    int lenRight = 0;
    int lenLeft = 0;
    if(n->getRight() == NULL && n->getLeft() == NULL)
        return 0;
    else
    {
        if(n->getRight() != NULL)
            lenRight = 1 + getPathLength(n->getRight());
        if(n->getLeft() != NULL)
            lenLeft = 1 + getPathLength(n->getLeft());
        return std::max(lenRight, lenLeft);
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
