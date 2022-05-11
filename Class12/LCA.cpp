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
T lca(BinTree<T>* t,T obj1, T obj2)
{
    T* res = new T;
    bool aux = obj1 == obj2;
    std::function<bool(T,bool,bool)> f = [&,aux,res,obj1,obj2](T val, bool b1, bool b2)
        {
            bool b3 = (val == obj1) || (val == obj2);
            bool b4 = (b3 && b1) || (b3 && b2) || (b1 && b2) || (aux && b3);

            if (b4)
            {
                *res = val;
                return false;
            }

            return b1 || b2 || b3;


        };
    std::function<bool()> h = [](){return false;};

    foldA(t,f,h);
    
    //std::cout << ToString<T>::show(*res) << std::endl;
    return *res;

}

void example()
{
    BinTree<int>* root = new BinTree<int>(3);
        BinTree<int>* _1 = new BinTree<int>(5);
            BinTree<int>* _3 = new BinTree<int>(6);
            BinTree<int>* _4 = new BinTree<int>(2);
                BinTree<int>* _7 = new BinTree<int>(7);
                BinTree<int>* _8 = new BinTree<int>(4);
        BinTree<int>* _2 = new BinTree<int>(1);
            BinTree<int>* _5 = new BinTree<int>(0);
            BinTree<int>* _6 = new BinTree<int>(8);
    


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
    std::cout << "lca(5,1) = " <<  lca(root,5,1) << std::endl;
    std::cout << "lca(6,4) = " <<  lca(root,6,4) << std::endl;
    std::cout << "lca(6,8) = " <<  lca(root,6,8) << std::endl;
}


int main(int argc, char const *argv[])
{

    example();
    return 0;
}
