#include <iostream> 
#include <stdlib.h> 
#include <string>   
#include <cmath>    
#include <stdexcept>
#include <type_traits>
#include <list>
#include <functional>
#include "To_String.h"
#include "Tree.h"
#include "FoldTree.h"
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace Tree;
using namespace To_String;
using namespace foldTree;


template <typename T>
T _lca(BinTree<T>* t,T obj1, T obj2)
{

    bool b1 = t->value() >= obj1;
    bool b2 = t->value() <= obj2;
    if (b1 && b2)
        return t->value();
    if (b1)
        return _lca(t->left(),obj1,obj2);
    
    return _lca(t->right(),obj1,obj2);
    

}

template <typename T>
T lca(BinTree<T>* t,T obj1, T obj2)
{
    return _lca(t,MIN(obj1,obj2),MAX(obj1,obj2));
}

void example()
{
    BinTree<int>* root = new BinTree<int>(6);
        BinTree<int>* _1 = new BinTree<int>(2);
            BinTree<int>* _3 = new BinTree<int>(0);
            BinTree<int>* _4 = new BinTree<int>(4);
                BinTree<int>* _7 = new BinTree<int>(3);
                BinTree<int>* _8 = new BinTree<int>(5);
        BinTree<int>* _2 = new BinTree<int>(8);
            BinTree<int>* _5 = new BinTree<int>(7);
            BinTree<int>* _6 = new BinTree<int>(9);
    


    root->setLeft(_1);
    root->setRight(_2);

    _1->setLeft(_3);
    _1->setRight(_4);

    _4->setLeft(_7);
    _4->setRight(_8);

    _2->setLeft(_5);
    _2->setRight(_6);


    std::cout << ToString<BinTree<int> >::show(root) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "lca(5,3) = " <<  lca(root,5,3) << std::endl;
    std::cout << "lca(4,7) = " <<  lca(root,4,7) << std::endl;
    std::cout << "lca(0,5) = " <<  lca(root,0,5) << std::endl;
}


int main(int argc, char const *argv[])
{

    example();
    return 0;
}
