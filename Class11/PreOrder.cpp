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


BinTree<int>* solucion(std::list<int>* preorder)
{
    BinTree<int>* ret = new BinTree<int>(0);
    BinTree<int>* p = new BinTree<int>(preorder->front());
    ret->setLeft(p);
    preorder->pop_front();
    std::list<BinTree<int>*> stack;

    for(auto val : *preorder)
    {
        BinTree<int>* newNode = new BinTree<int>(val);
        if (val < p->value())
        {
            stack.push_front(p);
            p->setLeft(newNode);
            p = p->left();
        } else
        {
            while(!stack.empty() && stack.front()->value() < val)
            {
                p = stack.front();
                stack.pop_front();
            }
            p->setRight(newNode);
            p = p->right();
        }

        
    }

    return ret->left();

}

int main(int argc, char const *argv[])
{
    std::list<int> preoder;
    preoder.push_back(8);
    preoder.push_back(5);
    preoder.push_back(1);
    preoder.push_back(7);
    preoder.push_back(10);
    preoder.push_back(12);


    std::cout << ToString<BinTree<int> >::show(solucion(&preoder)) << std::endl;
    return 0;
}
