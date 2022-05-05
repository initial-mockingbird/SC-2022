#include <iostream> 
#include <stdlib.h> 
#include <string>   
#include <cmath>    
#include <stdexcept>
#include <type_traits>
#include <list>
#include <functional>

#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)


template<typename T>
class TreeNode{
    public:
        T            value;
        TreeNode<T>* left;
        TreeNode<T>* right;
};

template <typename T>
class BinTree{
    
    public:
    BinTree(){
        this->root = NULL;
    }

    BinTree(T value){
        this->root = new TreeNode<T>;
        this->root->value = value;
    }

    bool isLeaf() const{
        return this->root == NULL;
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
        return new BinTree(this->root->left);
    }

    BinTree<T>* right() const{
        if (this->isLeaf())
        {
            return new BinTree();
        }
        return new BinTree(this->root->right);
    }

    void setValue(T value){
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
        *this = *BinTree(value);
        this->setLeft(left);
        this->setRight(right);
    }

    
    private:

    BinTree(TreeNode<T>* root){
        this->root=root;
    }

    TreeNode<T>* root;
          
};


template <typename T>
class ToString
{
    public:
        static const bool is_specialized = false;
        static std::string show(T);
};

template <>
class ToString<int>
{
public:
    static const bool is_specialized = true;
    static std::string show(int i){
        return std::to_string(i);
    }
};


template <typename T>
class ToString<BinTree<T> >
{
public:
    static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
    static const bool is_specialized = true;
    static std::string show(BinTree<T>* tree){
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


template <typename T>
class ToString<std::list<T> >
{
public:
    static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
    static const bool is_specialized = true;
    static std::string show(std::list<T>* l)
    {   
        std::string res = "";
        for (auto c : *l)
            res += ToString<T>::show(c) + " -> ";
        
        return res + "nil";
    }
};


template < template<typename A> class C, typename A, typename B>
class Foldable
{
public:
    static const bool is_specialized = false;
    static B fold(std::function<B(B,A)>, B, C<A>*);
    static int length(C<A>* t);
    static A   min(C<A>* t);
    static A   max(C<A>* t);
    static std::list<A>* toList(C<A>* t);
};


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


int main(int argc, char const *argv[])
{
    BinTree<int>* t = new BinTree<int>(10);
    t->setLeft(new BinTree<int>(5));
    t->setRight(new BinTree<int>(20));

    t->right()->setLeft(new BinTree<int>(15));

    std::cout << ToString<BinTree<int> >::show(t) << std::endl;

    std::cout << Foldable<BinTree,int,int>::length(t) << std::endl;


    std::list<int>* res = Foldable<BinTree,int,int>::toList(t);
    std::cout << ToString<std::list<int> >::show(res) << std::endl;

    /*
    // Error a tiempo de compilacion.
    BinTree<float>* tf;
    std::cout << ToString<BinTree<int> >::show(tf) << std::endl;
    */
    return 0;
}
