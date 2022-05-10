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




void kSmallest(BinTree<int>* t, int* k, int* res)
{

    if (t->isLeaf())
        return ;
    
    kSmallest(t->left(),k,res);

    if (*k == 1)
    {
        *res = t->value();
        *k   = 0;
        return ; 
    }

    *k = MAX(*k - 1,0);

    if (*k <= 0)
        return;

    kSmallest(t->right(),k,res);

}

int main(int argc, char const *argv[])
{
    std::list<Node> in;

    in.push_back(*new Node(5)  );
    in.push_back(*new Node(3)  );
    in.push_back(*new Node(6)  );
    in.push_back(*new Node(2)  );
    in.push_back(*new Node(4)  );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node(1)  );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );
    in.push_back(*new Node()   );


    BinTree<int>* bt = fromLevelOrder(in);
    int k = 3;
    int res = -10;
    kSmallest(bt,&k,&res);

    std::cout << ToString<BinTree<int> >::show(bt)  << std::endl;
    std::cout << res  << std::endl;
    
    return 0;
}
