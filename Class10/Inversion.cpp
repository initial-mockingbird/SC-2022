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


void sol(BinTree<int>* t)
{

    if (t->isLeaf())
        return ;

    sol(t->left());
    sol(t->right());

    BinTree<int>* l = t->left();
    BinTree<int>* r = t->right();

    t->setLeft(r);
    t->setRight(l);

}

int main(int argc, char const *argv[])
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

    sol(bt);

    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;
    return 0;
}
