#include <iostream> // Para imprimir
#include <stdexcept>
#include <functional>

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



int add(int x, int y){
    return x+y;
}

int length_fun(int _,int b){
    return b++;
}




template < template<typename A> class C, typename A, typename B>
class Foldable
{
public:
    static const bool is_specialized = false;
    static B foldl(std::function<B(A,B)>, B, C<A>*);
    static int length(C<A>* t);
    static const int spooky_number = 10; 
};


/*
l [1,2,3,4] = 1 + 2 + 3 + 4 =  10

int res = 0;
while !(l.isEmpty()){
    res = l.head() + res;
    l = l.tail();
}

return res

((((1 + 0) + 2) + 3) + 4) = 10
((((1 op 0) op 2) op 3) op 4) 
((((1 op acc) op 2) op 3) op 4) 




foldl(op,acc,lista)
{
    int res = acc;
    while !(l.isEmpty())
    {
        res = op(l.head(),res);
        l = l.tail();
    }

    return res
}

int aux(int _, int x){
    return x++;
}

foldl(+,0,lista) <- la suma de los elementos de la lista
foldl(*,1,lista) <- la multiplicacion de los elementos de la lista
foldl(aux,0,lista) <- la longitud de la lista

4 
*/

template <typename A, typename B>
    class Foldable<SLL,A,B>
    {
    public:
        static B foldl(std::function<B(A,B)>f ,B acc, SLL<A>* l)
        {
            SLL<A>* temp = l;
            while (! temp->isEmpty())
            {
                acc = f(acc,temp->unsafeHead());
                temp = temp->tail();
            }

            return acc;
        }
        static int length(SLL<A>* t) {return Foldable<SLL,A,B>::foldl(length_fun,0,t); };
        static const bool is_specialized = true;
        static const int spooky_number   = 50;
        static const int list_only       = 1212;
    };


template <typename T>
class BST : public 




int main(int argc, const char** argv) 
{   
    SLL<int> listica;
    listica.push(4);
    listica.push(3);
    listica.push(2);
    listica.push(20);

    std::cout << Foldable<SLL,int,int>::spooky_number << std::endl;
    std::cout << Foldable<SLL,int,int>::foldl(add, 0, &listica) << std::endl;
    // funciones anonimas
    // funciones lambda
    // expresiones lambda?
    std::cout << Foldable<SLL,int,int>::foldl([](int x, int y){return x+y;}, 0, &listica) << std::endl;
    std::cout << Foldable<SLL,int,int>::length(&listica) << std::endl;

    /*
    std::cout << Foldable<SLL<int> >::length(&listica) << std::endl;
    std::cout << Foldable<SLL<int> >::spooky_number << std::endl;
    std::cout << Foldable<SLL<int> >::list_only << std::endl;
    */
    return 0;
}