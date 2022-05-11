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
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace FoldableM;
using namespace To_String;
using namespace Tree;



enum class NodeType {Null,Content};
class Node
{ 
public:
    Node()
    {
        this->tag = NodeType::Null;
    }
    Node(int value)
    {
        this->tag   = NodeType::Content;
        this->value = value;
    }
    NodeType tag;
    int value;
};

BinTree<int>* fromLevelOrder(std::list<Node> l)
{
    if (l.empty())
        return new BinTree<int>;

    std::list<BinTree<int>*> current;
    std::list<BinTree<int>*> next;
    Node j;
    BinTree<int>* subTree;
    BinTree<int>* root = new BinTree<int>(l.front().value);
    BinTree<int>* ret;

    l.pop_front();

    current.push_front(root);

    while (!l.empty())
    {
        while(!current.empty())
        {
            
            subTree = current.front();

            j = l.front();

            if (j.tag==NodeType::Content)
            {
                subTree->setLeft(new BinTree<int>(j.value));
                next.push_back(subTree->left());
            }
            
            l.pop_front();
            j = l.front();
            
            if (j.tag==NodeType::Content)
            {
                subTree->setRight(new BinTree<int>(j.value));
                next.push_back(subTree->right());
            }
            
            current.pop_front();
            l.pop_front();
            
            
            ret = new BinTree<int>(root->value());
            /*
            ret->setLeft(root->left());
            ret->setRight(root->right());
            */
        }
        current.swap(next);

    }

    return root;
}

template <typename T>
bool isLeafNode(BinTree<T>* t)
{
    return !t->isLeaf() && t->left()->isLeaf() && t->right()->isLeaf();


}

template <typename T, typename B>
B foldA(BinTree<T>* t,std::function<B(T,B,B)> f,std::function<B(T)> g)
{
    if (isLeafNode<T>(t))
    {
        return g(t->value());
    }

    B left = foldA(t->left(),f,g);
    B right = foldA(t->right(),f,g);

    return f(t->value(),left,right);

}

template <typename T, typename B>
B foldA2(BinTree<T>* t,std::function<B(T,B,B)> f,std::function<B()> gen)
{
    if (t->isLeaf())
    {
        return gen();
    }

    B left = foldA2(t->left(),f,gen);
    B right = foldA2(t->right(),f,gen);

    return f(t->value(),left,right);

}

template <typename T>
int maximumDepth(BinTree<T>* t)
{
    return foldA2<T,int>(t,[](T _, int l, int r){return 1 + MAX(l,r);} ,[](){return 0;});
}

template <typename T>
int minimumDepth(BinTree<T>* t)
{
    return foldA2<T,int>(t,[](T _, int l, int r){return 1 + MIN(l,r);} ,[](){return 0;});
}


template<typename T>
BinTree<T>* invertTree(BinTree<T>* t)
{
    return foldA2<T,BinTree<T>*>
        (t,
        [](T n, BinTree<T>* l, BinTree<T>* r){return new BinTree<T>(n,r,l);},
        [](){return new BinTree<T>;}
        );
}



template<typename A,typename B>
std::list<B>* mapList(std::list<A>* l,std::function<B(A)>f)
{
    std::list<B>* ret = new std::list<B>;
    for(auto var : *l)
    {
        ret->push_back(f(var));
    }

    return ret;
}




template <typename T>
std::list<T>* concat(std::list<T>* x1, std::list<T>* x2)
{
    x1->splice(x1->end(),*x2);
    return x1;
}


bool pathSum(BinTree<int>* t, int target)
{
    std::list<int>* l = foldA2<int,std::list<int>* >
        (t,
        [](int n,std::list<int>* l, std::list<int>* r){ return mapList<int,int>(concat<int>(l,r),[n](int p){return p-n;}); },
        [target](){std::list<int>* l = new std::list<int>(); l->push_front(target); return l; }
        );


    for(auto var : *l)
    {
        if (var == 0)
            return true;
    }

    return false;
}

void maxDepthEx()
{
    std::list<Node> in;

    in.push_back(*new Node(3)  );
    in.push_back(*new Node(9)  );
    in.push_back(*new Node(20) );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node(15) );
    in.push_back(*new Node(7)  );
   
    BinTree<int>* bt = fromLevelOrder(in);

    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;



    std::cout << maximumDepth(bt) << std::endl;
    
}

void invertEx()
{
    std::list<Node> in;

    in.push_back(*new Node(3)  );
    in.push_back(*new Node(9)  );
    in.push_back(*new Node(20) );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node(15) );
    in.push_back(*new Node(7)  );
   


    BinTree<int>* bt = fromLevelOrder(in);

    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;


    std::cout << ToString<BinTree<int> >::show(invertTree(bt))  << std::endl;
}

void treeSumsEx()
{
    std::list<Node> in;

    in.push_back(*new Node(5)  );
    in.push_back(*new Node(4)  );
    in.push_back(*new Node(8)  );
    in.push_back(*new Node(11) );
    in.push_back(*new Node()   );
    in.push_back(*new Node(13) );
    in.push_back(*new Node(4)  );
    in.push_back(*new Node(7)  );
    in.push_back(*new Node(2)  );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node(1)  );

    BinTree<int>* bt = fromLevelOrder(in);

    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;

    int target = 22;

    bool b = pathSum(bt,target);

    std::cout << b << std::endl;
}

int main(int argc, char const *argv[])
{
    //maxDepthEx();
    //invertEx();
    treeSumsEx();
    return 0;
}

