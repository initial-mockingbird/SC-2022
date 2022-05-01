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

    bool isEmpty(){
        return this->head == NULL;
    }

    T unsafeHead(){
        return this->head->value;
    }

    SLL<T>* tail(){
        return SLL(this->head->next);
    }

    // polimorfica
    void push(T x){

        /*
        5

        1->2->3

        newHead.value=?
        newHead.next=NULL

        ? -> NULL

        5 -> NULL

        5->1->2->3

        */

        ListNode<T>* newHead = new ListNode<T>;
        newHead->value = x;        
        newHead->next  = this->head;
        this->head     = newHead;
    }

    T pop(){

        /*
        SLL
        V
        5->1->2->3
        
          SLL
           v
        5->1->2->3
        ^
        x

        */

        T v = this->unsafeHead();
        ListNode<T>* temp = this->head;
        this->head = this->head->next;
        delete temp;
        return v;
    }

    T get(int i)
    {
        ListNode<T>* temp = this->head;
        
        for (; i > 0; i--)
            temp = temp->next;

        return temp->value;
    }

    T operator[](int i){
        ListNode<T>* temp = this->head;
        
        for (; i > 0; i--)
            temp = temp->next;

        return temp->value;
    };

    int length()
    {
        // 1 -> 2 -> 3 -> 4 -> NULL
        // ^         ^
        // 1    +    3 = 4


        /*
        2 -> 3 -> 4 -> NULL

        */

        SLL<T> temp = SLL(this->head);
        int i = 0;
        while(!temp.isEmpty())
        {
            i++;
            temp.pop();
        }

        return i;

    }

    /* SOLUCION PROTIPO
    int length()
    {

        ListNode<T> temp = this->head;
        int i = 0;
        while(temp != NULL)
        {
            i++;
            temp= temp->next;
        }

        return i;

    }
    */
   
   int length2()
    {
        // 1 -> 2 -> 3 -> 4 -> NULL
        // ^         ^
        // 1    +    3 = 4


        /*
        2 -> 3 -> 4 -> NULL
        ^       ^
        1   +   2 = 3
        */

       if (this->isEmpty())
       {
           return 0;
       }

        SLL<T> temp = this->tail();
        return 1 + temp.length();
    }

    // 1->2->3->NULL
    // 5->6->7->NULL
    // 1->2->3->5->6->7->NULL

    /*
    lista3 = lista1 + (lista2 + lista3);
    lista3 = (lista1 + lista2) + lista3;

    lista3 == lista3 ++ SLL();
    */

   
    
    private:
    SLL(ListNode<T>* head){
        this->head=head;
    }
    ListNode<T>* head;

friend SLL<T> operator+(SLL<T> const &lista1, SLL<T> const &lista2)
    {
        if (lista1.isEmpty())
        {
            return lista2;
        }

        SLL<T> res   = lista1.tail() + lista2;
        res.push(lista1.unsafeHead());

        return res; 
    }             
};




int main(int argc, const char** argv) {

    SLL<int> listica;
    listica.push(3);
    listica.push(4);
    

    SLL<int> listica2;
    listica2.push(1);
    listica2.push(2);

    
    SLL<int> listica3 = listica + listica2;
    return 0;
}