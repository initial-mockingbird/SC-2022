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



#ifndef BST_H // include guard
#define BST_H

namespace bst
{
    using namespace To_String;
    template <typename T>
    class BST
    {
        public:

        Tree::BinTree<T>* bst;

        BST()
        {
            this->bst = new Tree::BinTree<T>;
        }

        BST(T value)
        {
            this->bst = new Tree::BinTree<T>(value);
        }

        void insert(T value)
        {
            Tree::BinTree<T>* insertionNode = new Tree::BinTree<T>(value);
            Tree::BinTree<T>* bst = this->bst;

            if (this->bst->isLeaf())
            {
                this->bst = insertionNode;
                return ;
            }
                
            while (!bst->isLeaf())
            {
                if (bst->value()==value)
                    return;
            
                if(value < bst->value())
                {
                    if(bst->left()->isLeaf())
                    {
                        bst->setLeft(insertionNode);
                        return ;
                    } else
                    {
                        bst = bst->left();
                    }
                    
                } else
                {
                    if(bst->right()->isLeaf())
                    {
                        bst->setRight(insertionNode);
                        return;
                    } else
                    {
                        bst = bst->right();
                    }
                }
                
            }
            
        }

        void remove(T value)
        {
            Tree::BinTree<T>* bst = this->bst;

            if (this->bst->isLeaf())
            {
                return ;
            }
                

            while (!bst->isLeaf())
            {
                
                if (bst->value()==value)
                {
                    if (bst->left()->isLeaf() && bst->right()->isLeaf())
                    {   
                        delete(bst->left());
                        delete(bst->right());
                        bst->setLeaf();
                    }else if (bst->left()->isLeaf())
                    {
                        delete(bst->left());
                        *bst = *(bst->right());

                    }else if (bst->right()->isLeaf())
                    {
                        delete(bst->right());
                        *bst = *(bst->left());
                    }else
                    {
                        T succ = this->_removeSucc(bst);
                        bst->setValue(succ);
                    }

                    return ;
                    
                }else if(value < bst->value())
                {   
                    bst = bst->left();  
                    
                } else
                {
                    bst = bst->right();
                }
                
            }
        }


        private:
        friend class ToString<BST<T> >;

        BST(Tree::BinTree<T>* bst)
        {
            this->bst = bst;
        }

        T _removeSucc(Tree::BinTree<T>* bst)
        {
            Tree::BinTree<T>* succ = bst->right();
            while(!succ->left()->isLeaf())
            {
                succ = succ->left();
            }

            T v = succ->value();
            BST<T>* wrap = new BST<T>(succ);
            wrap->remove(v);
            return v;

        }

        
    };

}

namespace To_String
{
    using namespace bst;
    template <typename T>
    class ToString<BST<T> >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(BST<T>* tree){
            return ToString<BinTree<T> >::show(tree->bst);
        }
    };
    
} // namespace name


#endif /* BST_H */