#include <iostream> 
#include <stdlib.h> 
#include <string>   
#include <cmath>    
#include <stdexcept>
#include <type_traits>
#include <list>
#include <vector>
#include <functional>
#include "To_String.h"
#include "Tree.h"
#include "FoldTree.h"
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace Tree;
using namespace To_String;
using namespace foldTree;
using namespace FoldableM;


void dp(std::vector<int>* l, std::vector<int>* mem, int n)
{
    
    if (n >= l->size())
        return;
        
    dp(l,mem,n+1);
    dp(l,mem,n+2);

    (*mem)[n] = MAX((*l)[n] + (*mem)[n+2],(*mem)[n+1]);

    return;

}

template <typename T>
void toVector(BinTree<T>* t, std::vector<T>* v,bool b)
{
    if (t->isLeaf())
        return;
    
    if (b)
        v->push_back(t->value());
    toVector(t->left(),v,b);
    toVector(t->right(),v,b);
    
    if (!b)
        v->push_back(t->value());
}

int sol(BinTree<int>* t)
{

    std::vector<int>* l = new std::vector<int>;
    toVector(t->left(),l,false);
    l->push_back(t->value());
    toVector(t->right(),l,true);

    int n = Foldable<BinTree,int,int>::length(t);
    std::vector<int>* mem = new std::vector<int>(n+2);
    std::cout << ToString<std::vector<int> >::show(*l) << std::endl;
    std::cout << ToString<std::vector<int> >::show(*mem) << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    dp(l,mem,0);
    int ret = 0;
    for (size_t i = 0; i < n; i++)
        ret = MAX(ret,(*mem)[i]);
    
    return ret;

}

void example()
{
    BinTree<int>* root = new BinTree<int>(3);
        BinTree<int>* _1 = new BinTree<int>(2);

            BinTree<int>* _4 = new BinTree<int>(3);

        BinTree<int>* _2 = new BinTree<int>(3);
            
            BinTree<int>* _6 = new BinTree<int>(1);

    root->setLeft(_1);
    root->setRight(_2);

    _1->setRight(_4);

    _2->setRight(_6);

    std::cout << ToString<BinTree<int> >::show(root) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << sol(root) << std::endl;
}


int main(int argc, char const *argv[])
{

    example();
    return 0;
}
