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
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace Tree;
using namespace To_String;
template <typename T>
void sol(BinTree<T>* _t)
{
    std::list<BinTree<T>*> current;
    std::list<BinTree<T>*> next;
    BinTree<T>* currentT;
    std::list<T> res;
    current.push_back(_t);



    while (current.size() > 0)
    {   

        for(auto t : current)
        {   
            if (!t->left()->isLeaf())
                next.push_back(t->left());
            if (!t->right()->isLeaf())
                next.push_back(t->right());
        }

        res.push_back(current.back()->value());

        std::swap(current,next);
        next.clear();
    }

    std::cout << ToString<std::list<T> >::show(res) << std::endl;
    

}

void example()
{
    BinTree<int>* root = new BinTree<int>(1);
    BinTree<int>* _1 = new BinTree<int>(2);
    BinTree<int>* _2 = new BinTree<int>(3);
    BinTree<int>* _3 = new BinTree<int>(5);
    BinTree<int>* _4 = new BinTree<int>(4);

    _1->setRight(_3);
    _2->setRight(_4);

    root->setLeft(_1);
    root->setLeft(_2);

    sol(root);
}


int main(int argc, char const *argv[])
{

    example();
    return 0;
}
