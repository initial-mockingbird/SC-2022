#include <iostream> // Para imprimir
#include <stdlib.h> // Malloc/free
#include <string>   // Jupyter no permite cosas tipo cout << 0.5 por cuestiones de tipo (<< esta definido
                    // tanto para strings como para numeros, cual deberia tomar? error!), asi que necesitamos castear cada cosa a string.
#include <cmath>    // math
#include <utility>
#include <unordered_map>
#include <iterator>
#include <list>
#include <stack>
#include <tuple>
#include <stdexcept>
#include <set>

template<typename T>
class ListNode{
    public:
        T            value;
        ListNode<T>* next;
};

template <typename T>
// Single Linked List <- llista simplemente enlazada
class SLL{
    
    public:
    SLL(){
        this->head = NULL;
    }

    bool isEmpty() const{
        return this->head == NULL;
    }

    T unsafeHead() const{
        return this->head->value;
    }

    SLL<T>* tail() const{
        return new SLL(this->head->next);
    }

    void push(T x){

        ListNode<T>* newHead = new ListNode<T>;
        newHead->value = x;        
        newHead->next  = this->head;
        this->head     = newHead;
    }

    SLL<T>* operator+(SLL<T>& b){
        SLL<T>* res = new SLL<T>;

        if (this->isEmpty()){
            res = &b;
            return res;
        }
            

        res = *(this->tail()) + b;
        res->push(this->unsafeHead());

        return res;
    }

    T pop(){
        T v = this->unsafeHead();
        ListNode<T>* temp = this->head;
        this->head = this->head->next;
        delete temp;
        return v;
    }

    T get(int i) const
    {
        ListNode<T>* temp = this->head;
        
        for (; i > 0; i--)
            temp = temp->next;

        return temp->value;
    }

    T operator[](int i) const{
        ListNode<T>* temp = this->head;
        
        for (; i > 0; i--)
            temp = temp->next;

        return temp->value;
    };
    
    private:

    SLL(ListNode<T>* head){
        this->head=head;
    }
    ListNode<T>* head;
          
};



/* general numeric limits as default for any type */
template <class T>
class Foldable
{
public:
    // no specialization for numeric limit exists
    static const bool is_specialized = false;
    static int length(T*);
    static const int spooky_number = 10;
};

template <typename T>
    class Foldable<SLL<T> >
    {
    public:
        // Now we have a specialization for numeric limit for int.
        // It does exists.
        static const bool is_specialized = true;
        static int length(SLL<T>* l) throw() {
            if (l->isEmpty())
            {
                return 0;
            }
            SLL<T>* temp = l->tail();
            return 1 + Foldable<SLL<T> >::length(temp);
        }
        static const int spooky_number = 50;
        static const int list_only     = 1212;
    };


int main(int argc, const char** argv) 
{   
    SLL<int> listica;
    listica.push(4);
    listica.push(3);
    listica.push(2);
    listica.push(20);

    std::cout << Foldable<SLL<int> >::length(&listica) << std::endl;
    std::cout << Foldable<SLL<int> >::spooky_number << std::endl;
    std::cout << Foldable<SLL<int> >::list_only << std::endl;
    return 0;
}