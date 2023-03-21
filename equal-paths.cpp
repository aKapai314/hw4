#ifndef RECCHECK
#include <algorithm>
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int getPathLength(Node* n);


bool equalPaths(Node * root)
{
    if(root == NULL)
        return true;
    if(root->right == NULL && root->left == NULL)
        return true;
    else if(root->right == NULL)
        return equalPaths(root->left);
    else if(root->left == NULL)
        return equalPaths(root->right);
    else
    {
        if(equalPaths(root->right) == equalPaths(root->left))
        {
            if(getPathLength(root->right) == getPathLength(root->left))
                return true;
        }
    }
    return false;

}

int getPathLength(Node* n)
{
    int lenRight = 0;
    int lenLeft = 0;
    if(n->right == NULL && n->left == NULL)
        return 0;
    else
    {
        if(n->right != NULL)
            lenRight = 1 + getPathLength(n->right);
        if(n->left != NULL)
            lenLeft = 1 + getPathLength(n->left);
        return std::max(lenRight, lenLeft);
    }


}



