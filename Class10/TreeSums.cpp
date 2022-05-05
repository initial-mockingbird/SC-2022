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


bool sol(BinTree<int>* t, int* target,std::list<int>* res)
{
    if (t->isLeaf())
        return true;

    bool b = false;    
    *target = *target - t->value();
    int n = *target;
    res->push_back(t->value());


    if (!t->left()->isLeaf())
    {
        b = sol(t->left(),target,res);

        if (b && *target == 0)
            return b;

        *target = n;
        res->pop_back();
        b = false;
    }
    
    if (!t->right()->isLeaf())
    {
        b = sol(t->right(),target,res);
        if (b && *target == 0)
            return b;

        *target = n;
        res->pop_back();
        b = false;
    }
    
    return b;
}

int main(int argc, char const *argv[])
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


    std::list<int> l;
    int target = 22;

    bool b = sol(bt,&target,&l);

    std::cout << b << std::endl;
    std::cout << ToString<std::list<int> >::show(l) << std::endl;

    return 0;
}
