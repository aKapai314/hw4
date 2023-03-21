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
    virtual void rotateRight(AVLNode<Key,Value>* n); 
    virtual void rotateLeft(AVLNode<Key,Value>* n);
    int calcBalance(AVLNode<Key,Value>* n);
    void insertFix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    void removeFix(AVLNode<Key,Value>* p, int diff);
    AVLNode<Key, Value>* internalFind(const Key& key) const;
		AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current);



};

template<class Key, class Value>
int AVLTree<Key, Value>::calcBalance(AVLNode<Key,Value>* n)
{
    if(n == NULL)
        return 0;
    int leftHeight = getPathLength(n->getLeft());
    int rightHeight = getPathLength(n->getRight());

    return (rightHeight - leftHeight);

}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n)
{
	if(n->getLeft() == NULL)
		return;
	
	//cout << "the node to rotate right is " << n->getValue() << endl;
	if(n->getParent() != NULL) 
	{
		//cout << "the OG parent of n is " << n->getParent()->getValue() << endl;
		AVLNode<Key,Value>* oldParent = n->getParent();
		if(oldParent->getRight() == n) //if n is the right child
			oldParent->setRight(n->getLeft()); //set n's left child to the right child of parent
		else
			oldParent->setLeft(n->getLeft()); //otherwise set as left child
	}
	AVLNode<Key,Value>* newParent = n->getLeft();
	//cout << "new parent of node is " << newParent->getValue() << endl;
	if(n == this->root_)
		this->root_ = newParent;
	newParent->setParent(n->getParent()); //set the parent of n's OG left child to be n's OG parent
	
	n->setLeft(newParent->getRight()); //set n's left child to be it's old left child's right child

	if(newParent->getRight() != NULL)
		newParent->getRight()->setParent(n);
	//cout << "node's new left should be " << n->getLeft()->getValue() << endl;
	newParent->setRight(n); //set n's OG left child to have a right child of n
  //cout << "new parent's right node is " << newParent->getRight()->getValue() << endl;
	n->setParent(newParent);
	
	
	//cout << "after rotating right: " << endl;
	//this->BinarySearchTree<Key,Value>::printRoot(this->root_);

	


	
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
	if(n->getRight() == NULL)
		return;
	//cout << "the node to rotate left is " << n->getValue() << endl;
	if(n->getParent() != NULL) 
	{
		AVLNode<Key,Value>* oldParent = n->getParent();
		if(oldParent->getRight() == n) //if n is the right child
			oldParent->setRight(n->getRight()); //set n's left child to the right child of parent
		else
			oldParent->setLeft(n->getRight()); //otherwise set as left child
	}
	
	AVLNode<Key,Value>* newParent = n->getRight();
	if(n == this->root_)
		this->root_ = newParent;
	newParent->setParent(n->getParent()); //set the parent of n's OG left child to be n's OG parent
	n->setRight(newParent->getLeft()); //set n's left child to be it's old left child's right child
	
	if(newParent->getLeft() != NULL)
		newParent->getLeft()->setParent(n);
	
	newParent->setLeft(n); //set n's OG left child to have a right child of n
	n->setParent(newParent);
	//cout << "after rotating left:" << endl;
	//this->BinarySearchTree<Key,Value>::printRoot(this->root_);

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{
	//cout << "at the start of insertfix, node is " << n->getValue() << endl;
	if(p == NULL || p->getParent() == NULL)
		return;
	
	AVLNode<Key,Value>* g = p->getParent();

	if(g->getLeft() == p) //if p is a left child
	{
		//cout << "parent is a left child of gp" << endl;
		//cout << "balance of grandparent is: " << int(g->getBalance()) << endl;
		g->setBalance(g->getBalance() - 1);
		//cout << "grandparent is " << g->getValue() << endl;
		//cout << "parent is " << p->getValue() << endl;
		//cout << "node is " << n->getValue() << endl;
		
		//cout << "before fix, grandparent balance is " << int(g->getBalance()) << endl;
		if(g->getBalance() == 0)
			return;
		else if(g->getBalance() == -1)
			insertFix(p, g);
		else if(g->getBalance() == -2)
		{
			if(p->getLeft() == n){//if zig zig
				//cout << "zig zig right" << endl;
				rotateRight(g);
				p->setBalance(0);
				g->setBalance(0);
			}
			else if(p->getRight() == n){ //zig zag
				//cout << "zig zag left right" << endl;
				rotateLeft(p);
				rotateRight(g);
				//cout << "n balance is " << int(n->getBalance()) << endl;
				if(int(n->getBalance()) == -1){
					p->setBalance(0);
					g->setBalance(1);
					n->setBalance(0);
				}
				else if(int(n->getBalance()) == 0){
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
					
				}
				else if(int(n->getBalance()) == 1){
					p->setBalance(-1);
					g->setBalance(0);
					n->setBalance(0);
				}	
			}
		}
	}

	else if(g->getRight() == p)//if p is a right child
	{
		//cout << "parent is a right child of gp" << endl;
	
		g->setBalance(g->getBalance() + 1);
		//cout << "before fix, grandparent balance is " << int(g->getBalance()) << endl;
		if(g->getBalance() == 0)
			return;
		else if(g->getBalance() == 1)
			insertFix(p, g);
		else if(g->getBalance() == 2)
		{
			if(p->getRight() == n){//if zig zig
				//cout << "zig zig left" << endl;
				rotateLeft(g);
				p->setBalance(0);
				g->setBalance(0);
			}
			else if(p->getLeft() == n){ //zig zag
				//cout << "zig zag right left" << endl;
				rotateRight(p);
				rotateLeft(g);
				if(n->getBalance() == 1){
					p->setBalance(0);
					g->setBalance(-1);
					n->setBalance(0);
				}
				else if(n->getBalance() == 0){
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
				}
				else if(n->getBalance() == -1){
					p->setBalance(1);
					g->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
}
    

template<class Key, class Value>   
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int diff)
{
	int ndiff = 0;
	if(n == NULL)
		return;

	AVLNode<Key, Value>* p = n->getParent();
	
	if(p != NULL){
		if(p->getLeft() == n)
			ndiff = 1;
		else
			ndiff = -1;
	}
		

	if(diff == -1)
	{
		//Case 1
		if(n->getBalance() + diff == -2){
			AVLNode<Key, Value>* c = n->getLeft();
			//Case 1a
			if(c->getBalance() == -1){
				rotateRight(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			//Case 1b
			else if(c->getBalance() == 0){
				rotateRight(n);
				n->setBalance(-1);
				c->setBalance(1);
				return;
			}
			//Case 1c
			else if(c->getBalance() == 1){
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c);
				rotateRight(n);
				if(g->getBalance() == 1){
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0); 
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0); 
				}
				else if(g->getBalance() == -1){
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0); 
				}
				removeFix(p, ndiff);
			}
		}
		//Case 2
		else if(n->getBalance() + diff == -1)
		{
			n->setBalance(-1);
			return;
		}
		else if(n->getBalance() + diff == 0)
		{
			n->setBalance(0);
			removeFix(p, ndiff);
		}
	}
	else if(diff == 1)
	{
		//Case 1
		if(n->getBalance() + diff == 2){
			AVLNode<Key, Value>* c = n->getRight(); //check?
			//Case 1a
			if(c->getBalance() == 1){
				rotateLeft(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			//Case 1b
			else if(c->getBalance() == 0){
				rotateLeft(n);
				n->setBalance(1);
				c->setBalance(-1);
				return;
			}
			//Case 1c
			else if(c->getBalance() == -1){
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(c);
				rotateLeft(n);
				if(g->getBalance() == -1){
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0); 
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0); 
				}
				else if(g->getBalance() == 1){
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0); 
				}
				removeFix(p, ndiff);
			}
		}
		//Case 2
		else if(n->getBalance() + diff == 1)
		{
			n->setBalance(1);
			return;
		}
		else if(n->getBalance() + diff == 0)
		{
			n->setBalance(0);
			removeFix(p, ndiff);
		}
	}

}



/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
     AVLNode<Key, Value>* rmvNode = internalFind(key);

		if(rmvNode == NULL)
			return;

		if(rmvNode->getLeft() != NULL && rmvNode->getRight() != NULL) //if node has both children
		{
			AVLNode<Key, Value>* pred = predecessor(rmvNode);
			nodeSwap(pred, rmvNode);
			if(this->root_ == rmvNode)
				this->root_ = pred;
		}

		int diff = 0;;
		AVLNode<Key, Value>* parent = rmvNode->getParent();

		if(parent != NULL){
			if(parent->getLeft() == rmvNode) //node is a left child
				diff = 1;
			if(parent->getRight() == rmvNode) //node is a right child
				diff = -1;
		}

		if(rmvNode->getLeft() == NULL && rmvNode->getRight() == NULL) //if node has no children
		{
			if(rmvNode == this->root_) //if node has no parent
				this->root_ = NULL;
			else if(rmvNode->getParent()->getLeft() == rmvNode) //if node is a left child
				rmvNode->getParent()->setLeft(NULL);
			else //if node is a right child
				rmvNode->getParent()->setRight(NULL);
		}
		else if(rmvNode->getLeft() == NULL) //if node has only a right child
		{
			AVLNode<Key, Value>* rChild = rmvNode->getRight();
			if(rmvNode == this->root_){ //if node has no parent
				this->root_ = rChild;
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
			AVLNode<Key, Value>* lChild = rmvNode->getLeft();

			if(rmvNode == this->root_){ //if node has no parent
				this->root_ = lChild;
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

		removeFix(parent, diff);
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
  // TODO
    AVLNode<Key, Value>* next = current;
    
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





/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
  Key key = new_item.first;
  AVLNode<Key, Value>* next = internalFind(key);

	if(next != NULL)
		next->setValue(new_item.second);
	else
	{
		//dynamically allocate a new Node with inputted key/value
		AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		//cout << "adding key " << key << endl;
		if(this->root_ == NULL){
			//cout << "root is null, adding node and returning" << endl;
			this->root_ = newNode;
      static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0);
			return;
		}
		//start at the top of the tree
        else{
            next = static_cast<AVLNode<Key, Value>*>(this->root_);
            while(next != NULL)
            {
                if(key > next->getKey()) //go to the right
                {
									//cout << "going right" << endl;
                    //cout << "at node " << next->getKey() << ", going right" << endl;
                    if(next->getRight() == NULL) //if there's an empty spot
                    {
                        newNode->setParent(next);
                        next->setRight(newNode);
												//cout << "there's an empty spot" << endl;
												//this->BinarySearchTree<Key,Value>::printRoot(this->root_);
                        break;
                    }
                    next = next->getRight();
                }
                else //go to the left
                {
										//cout << "going left" << endl;
                    //cout << "at node " << next->getValue() << ", going left" << endl;
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
						//cout << "inserted node, now setting balance and fixing" << endl;
            newNode->setBalance(0);
						//cout << "do i make it here?" << endl;
						//cout << "value of n is " << newNode->getValue() << endl;

						
            if(newNode->getParent()->getBalance() == -1 || newNode->getParent()->getBalance() == 1){
                //cout << "balance of parent is " << next->getParent()->getBalance() << endl;
								newNode->getParent()->setBalance(0);
								//cout << "balance of parent set at 0" << endl;
								//this->BinarySearchTree<Key,Value>::printRoot(this->root_);
								//cout << "balance of newNode parent is finally " << newNode->getParent()->getBalance();
								//cout << "pt 2: value of n is " << newNode->getValue() << endl;
                return;
            }
            else if(newNode->getParent()->getLeft() == newNode){ //n is a left child & balance was 0
                //cout << "n is a left child " << endl;
								newNode->getParent()->setBalance( int(newNode->getParent()->getBalance()) - 1);
								//cout << "pt 2: value of n is " << newNode->getValue() << endl;
							//	cout << "balance of parent now  " << int(newNode->getParent()->getBalance()) << endl;
                insertFix(newNode, newNode->getParent());
								//cout << "pt 3: value of n is " << newNode->getValue() << endl;
								//cout << "balance of newNode parent is finally " << newNode->getParent()->getBalance();
            } //n is a right child & balance was 0
            else{
								//cout << "n is a right child " << endl;
                newNode->getParent()->setBalance( int(newNode->getParent()->getBalance()) + 1);  
								//cout << "pt 2: value of n is " << newNode->getValue() << endl;
								//cout << "balance of parent now " << int(newNode->getParent()->getBalance()) << endl;
                insertFix(newNode, newNode->getParent());
								//cout << "pt 3: value of n is " << newNode->getValue() << endl;
								//cout << "balance of newNode parent is finally " << newNode->getParent()->getBalance();
            }

						//this->BinarySearchTree<Key,Value>::printRoot(this->root_);
        }
	} 
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		//cout << "in the avl find function " << endl;
    AVLNode<Key, Value>* next = static_cast<AVLNode<Key, Value>*>(this->root_);

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

#endif
