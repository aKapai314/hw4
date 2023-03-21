#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    
     /*
		BinarySearchTree<char,int> bt;

        bt.insert(std::make_pair(1,9));
        bt.insert(std::make_pair(0,8));

        bt.print();
   
		bt.insert(std::make_pair(2,8));
		bt.insert(std::make_pair(1,-50));
		bt.insert(std::make_pair(3,0));
		bt.insert(std::make_pair(10,0));
		bt.insert(std::make_pair(15,0));
		

		int count = 0;
	
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
				count++;
    }

		cout << "Before any removals, tree is: " << endl;
		
		bt.print();

		bt.remove(-1);

		std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	
		bt.print();

		bt.remove(2);

		std::cout << "After removing 2 (the root), tree is: " << std::endl;

		bt.print();

		bt.remove(10);

		std::cout << "After removing 10, tree is: " << std::endl;

		bt.print();

		bt.remove(1);

		std::cout << "After removing 1, tree is: " << std::endl;

		bt.print();

	
	
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
		
    */
		
		    // AVL Tree Tests
    
    AVLTree<char,int> at;

    at.insert(std::make_pair(2,2));
    at.insert(std::make_pair(1,1));
    at.print();
    at.insert(std::make_pair(0,0));

    at.print();

    /*
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
    */
		
    return 0;
}
