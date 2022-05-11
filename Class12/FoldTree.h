#pragma once 
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



#ifndef FoldTree_H // include guard
#define FoldTree_H

namespace foldTree
{
    using namespace Tree;

    template <typename T, typename B>
    B foldA(BinTree<T>* t,std::function<B(T,B,B)> f,std::function<B()> gen)
    {
        if (t->isLeaf())
        {
            return gen();
        }

        B left = foldA(t->left(),f,gen);
        B right = foldA(t->right(),f,gen);

        return f(t->value(),left,right);

    }

} // namespace Tree


#endif /* FoldTree_H */