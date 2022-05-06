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
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)



#ifndef Tree_H // include guard
#define Tree_H

namespace Tree
{
    
    enum class TEnum {Leaf,Node};

    template<typename T>
    class TreeNode{
        public:

            TreeNode<T>* getLeft()
            {
                if (this->left == NULL)
                    this->left = new TreeNode<T>;
                return this->left;
            }

            TreeNode<T>* getRight()
            {
                if (this->right == NULL)
                    this->right = new TreeNode<T>;
                return this->right;
            }

            TEnum tag = TEnum::Leaf;
            T            value;
            TreeNode<T>* left;
            TreeNode<T>* right;
    };

    template <typename T>
    class BinTree
    {
        
        public:
        BinTree(){
            this->root = new TreeNode<T>;
        }

        BinTree(T value){
            this->root = new TreeNode<T>;
            this->root->tag = TEnum::Node;
            this->root->value = value;
        }

        bool isLeaf() const{
            return this->root->tag == TEnum::Leaf;
        }

        void setLeaf(){
            this->root->tag = TEnum::Leaf;
        }

        T value() const{
            if (this->isLeaf()){
                throw std::domain_error( "Leafs have no value." );
            }
            return this->root->value;
        }

        BinTree<T>* left() const{
            
            if (this->isLeaf())
            {
                return new BinTree();
            }
            return new BinTree(this->root->getLeft());
        }

        BinTree<T>* right() const{
            if (this->isLeaf())
            {
                return new BinTree();
            }
            return new BinTree(this->root->getRight());
        }

        void setValue(T value){
            this->root->tag   = TEnum::Node;
            this->root->value = value;
        }

        

        void setLeft(BinTree<T>* left){
            if (this->isLeaf())
                throw std::domain_error( "Cannot set left child of a leaf." );
            this->root->left  = left->root;
        }

        void setRight(BinTree<T>* right){
            if (this->isLeaf())
                throw std::domain_error( "Cannot set right child of a leaf." );
            this->root->right  = right->root;
        }

        BinTree(T value, BinTree<T>* left,BinTree<T>* right){
            *this = *new BinTree<T>(value);
            this->setLeft(left);
            this->setRight(right);
        }

        
        private:

        BinTree(TreeNode<T>* root){
            this->root=root;
        }

        TreeNode<T>* root;
            
    };

} // namespace Tree

namespace FoldableM
{
    using namespace Tree;
    template <typename A, typename B>
    class Foldable<BinTree,A,B>
    {
        public:
            static const bool is_specialized = true;
            static B fold(std::function<B(B,A)>f ,B acc, BinTree<A>* t)
            {
                if (t->isLeaf())
                    return acc;
            
                return Foldable<BinTree,A,B>::fold(
                    f,
                    f(Foldable<BinTree,A,B>::fold(f,acc,t->left()),t->value()),
                    t->right()   
                    );
            }
            static int length(BinTree<A>* t) {return Foldable<BinTree,A,B>::fold([](auto i, auto _){return i+1;},0,t); };
            
            static int max(BinTree<A>* t) {return Foldable<BinTree,A,A>::fold([](A a, A b){return MAX(a,b);},t->value(),t); };
            
            static int min(BinTree<A>* t) {return Foldable<BinTree,A,A>::fold([](A a, A b){return MIN(a,b);},t->value(),t); };
            
            static std::list<A>* toList(BinTree<A>* t) 
            { return Foldable<BinTree,A,std::list<A>* >::fold([](std::list<A>* l, A a){l->push_back(a); return l;},new std::list<A>,t); 
            };    
    };
}

namespace To_String
{
    using namespace Tree;
    template <typename T>
    class ToString<BinTree<T> >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(BinTree<T>* tree)
        {  

            return ToString<BinTree<T> >::pShow(tree,"");
        }
        
    private:
        static std::string pShow(BinTree<T>* tree,std::string tabs){
            std::string ret = "";
            std::string newTabs = tabs + "\t";
            if (tree->isLeaf())
            {   
                return  "Leaf";
            }
            ret += "Value: " + ToString<T>::show(tree->value()) + "\n";
            ret += newTabs + "left : " + ToString<BinTree<T> >::pShow(tree->left(),newTabs+"\t") + "\n";
            ret += newTabs + "right: " + ToString<BinTree<T> >::pShow(tree->right(),newTabs+"\t") + "\n";
            return ret;
        }
    };
}

#endif /* Tree_H */