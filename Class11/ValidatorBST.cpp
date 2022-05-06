#include <iostream> 
#include <stdlib.h> 
#include <string>   
#include <cmath>    
#include <stdexcept>
#include <type_traits>
#include <list>
#include <functional>
#include "Foldable.h"
#include "To_String.h"
#include "Tree.h"
#include "BST.h"
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace Tree;
using namespace bst;

template <typename T>
bool validateBST(BinTree<T>* t)
{
    if (t->isLeaf())
        return true;
    
    bool p = true;
    bool q = true;

    if (!t->left()->isLeaf())
    {
        p = t->value() > t->left();
    } 
    
    if (!t->right()->isLeaf())
    {
        q = t->value() < t->right();
    }

    return p && q && validateBST(t->left()) && validateBST(t->right());

}


int main(int argc, char const *argv[])
{
    
    return 0;
}
