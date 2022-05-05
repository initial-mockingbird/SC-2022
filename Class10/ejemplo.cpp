#include <list>
#include <stdlib.h> 
#include <iostream> 
using namespace std;

class ejemplo
{
public:
    ejemplo()
    {
        this->valor = -1;
    }

    ejemplo(int valor)
    {
        this->valor = valor;
    }

    int valor;

};


ejemplo* funcion(int valor)
{
    ejemplo* puntero = new ejemplo(valor);
    list<ejemplo*> listica;
    list<ejemplo*> listica2;
    listica.push_front(puntero);
    listica2.push_front(listica.front());
    listica2.pop_front();
    listica.pop_front();
    //ejemplo* ret = new ejemplo(puntero->valor);
    return puntero;
};

int main(int argc, char const *argv[])
{
    cout << funcion(20)->valor << endl;
    return 0;
};