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
#include <limits.h>
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace Tree;
using namespace To_String;
using namespace foldTree;




int kadane(std::vector<int>* xs)
{
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;

    for(auto x : *xs)
    {
        maxEndingHere += x;
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
        if (maxEndingHere < 0)
            maxEndingHere = 0;
    }

    return maxSoFar;
}


int kadaneT(BinTree<int>* t)
{
    auto [ret,_] = foldA<int,std::tuple<int,int> >
        (t,
        [](int v, std::tuple<int,int> l, std::tuple<int,int> r)
        {
            int pvalue = v + MAX(std::get<1>(l),std::get<1>(r)); 
            int value  = MAX(std::get<0>(l),std::get<0>(r));
            value = MAX(value,pvalue);
            value = MAX(value,v+std::get<1>(l)+std::get<1>(r));
            return std::tuple<int, int>{value, pvalue};
        },
        [](){return std::tuple<int, int>{0, 0};});

    return ret;    
}

void exampleT()
{
    BinTree<int>* root = new BinTree<int>(-10);
        BinTree<int>* _1 = new BinTree<int>(9);
            
        BinTree<int>* _2 = new BinTree<int>(20);
            BinTree<int>* _5 = new BinTree<int>(15);
            BinTree<int>* _6 = new BinTree<int>(7);
    


    root->setLeft(_1);
    root->setRight(_2);

    _2->setLeft(_5);
    _2->setRight(_6);

    
    std::cout << ToString<BinTree<int> >::show(root) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout <<  kadaneT(root) << std::endl;
    
}

void exampleA()
{
    std::vector<int>* xs = new std::vector<int>;
    xs->push_back(-2);
    xs->push_back(-3);
    xs->push_back(4);
    xs->push_back(-1);
    xs->push_back(-2);
    xs->push_back(1);
    xs->push_back(5);
    xs->push_back(-3);

    std::cout << ToString<std::vector<int> >::show(xs) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout <<  kadane(xs) << std::endl;
    std::cout << "--------------------------------" << std::endl;
}


int main(int argc, char const *argv[])
{

    exampleA();
    exampleT();
    return 0;
}
