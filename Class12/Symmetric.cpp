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



template<typename T>
BinTree<T>* invertTree(BinTree<T>* t)
{
    return foldA<T,BinTree<T>*>
        (t,
        [](T n, BinTree<T>* l, BinTree<T>* r){return new BinTree<T>(n,r,l);},
        [](){return new BinTree<T>;}
        );
}

template<typename T>
bool eq(BinTree<T>* t1,BinTree<T>* t2)
{

    if (t1->isLeaf() || t2->isLeaf())
        return t1->isLeaf() && t2->isLeaf();

    return eq(t1->left(),t2->left())
    &&     eq(t1->right(),t2->right())
    &&     (t1->value() == t2->value())
    ;
}

template<typename T>
bool symmetric(BinTree<T>* ti)
{
    BinTree<T>* it = invertTree(ti);

    //return it == ti;
    return eq(it,ti);
}

void example()
{
    BinTree<int>* root = new BinTree<int>(3);
        BinTree<int>* _1 = new BinTree<int>(2);
            BinTree<int>* _3 = new BinTree<int>(3);
            BinTree<int>* _4 = new BinTree<int>(4);

        BinTree<int>* _2 = new BinTree<int>(2);
            BinTree<int>* _5 = new BinTree<int>(4);
            BinTree<int>* _6 = new BinTree<int>(3);

    root->setLeft(_1);
    root->setRight(_2);

    _1->setLeft(_3);
    _1->setRight(_4);

    _2->setLeft(_5);
    _2->setRight(_6);

    std::cout << ToString<BinTree<int> >::show(root) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << symmetric(root) << std::endl;
}


int main(int argc, char const *argv[])
{

    example();
    return 0;
}
