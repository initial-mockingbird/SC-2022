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



void kSuccs(BinTree<int>* t, std::list<int>* l, int k)
{

    if (t->isLeaf() || k < 0)
        return ;

    if (k == 0)
    {
        l->push_back(t->value());
        return ;
    }

    kSuccs(t->left(),l,k-1);
    kSuccs(t->right(),l,k-1);

}


int sol(BinTree<int>* t, std::list<int>* l, int target, int k)
{
    if (t->isLeaf())
        return -1;
    
    if (t->value()==target)
    {
        kSuccs(t,l,k);
        return 1;
    }


    int p = sol(t->left(),l,target,k);

    if (p > 0)
    {
        kSuccs(t->right(),l,k-p-1);
    }
    
    int q = sol(t->right(),l,target,k);

    if (q > 0)
    {
        kSuccs(t->left(),l,k-q-1);
    }

    if (k-p == 0 || k-q == 0)
    {
        l->push_back(t->value());
        return -1;
    }

    int m = MAX(p,q);

    if (m >= 0)
    {
        return m + 1;
    }
    
    return -1;
    

}

int main(int argc, char const *argv[])
{
    std::list<Node> in;

    in.push_back(*new Node(3)  );
    in.push_back(*new Node(5)  );
    in.push_back(*new Node(1)  );
    in.push_back(*new Node(6)  );
    in.push_back(*new Node(2)  );
    in.push_back(*new Node(0)  );
    in.push_back(*new Node(8)  );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node(7)  );
    in.push_back(*new Node(4)  );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
   


    BinTree<int>* bt = fromLevelOrder(in);
    std::list<int> l;
    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;

    sol(bt,&l,5,1);

    std::cout << ToString<std::list<int> >::show(l)  << std::endl;
    return 0;
}
