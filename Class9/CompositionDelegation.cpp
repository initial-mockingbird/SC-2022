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


class Animal{
    public:
        int edad = -1;
        void habla(){
            std::cout << "generic grrr" << std::endl;
        }
    private:
        int secret = -1;
};

class Perro : public Animal
{
    public:
        int edad = 5;
        void desastre()
        {
            std::cout << "no desastre, only woof" << std::endl;
        }
};

class Gato : public Animal
{
    public:
        int edad = 4;
        void habla()
        {
            std::cout << "miau" << std::endl;
        }

        void desastre()
        {
            std::cout << "utter and complete chaos" << std::endl;
        }
};


class PerroGato : public Animal
{
    public:
        Gato g;
        
        int edad = 1;
        void habla()
        {
            g.habla();
        }
        void desastre()
        {
            p.desastre();
        }
    private:
        Perro p;
        
        
};



int main(int argc, const char** argv) 
{
    PerroGato pg;

    std::cout << pg.edad << std::endl;
    pg.desastre();
    pg.habla();

    PerroGato pg2;

    pg2.edad = 20;

    std::cout << pg.edad << std::endl;
    std::cout << pg2.edad << std::endl;

    return 0;
}


