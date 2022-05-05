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

using namespace FoldableM;
using namespace To_String;
using namespace Tree;

int main(int argc, char const *argv[])
{
    BinTree<int>* t = new BinTree<int>(10);

    
    std::cout << ToString<BinTree<int> >::show(t) << std::endl;
    
    t->setLeft(new BinTree<int>(5));
    t->setRight(new BinTree<int>(20));

    t->right()->setLeft(new BinTree<int>(15));



    std::cout << Foldable<BinTree,int,int>::length(t) << std::endl;


    std::list<int>* res = Foldable<BinTree,int,int>::toList(t);
    std::cout << ToString<std::list<int> >::show(res) << std::endl;
    std::cout << ToString<std::list<int> >::show(res) << std::endl;
    
    return 0;
}