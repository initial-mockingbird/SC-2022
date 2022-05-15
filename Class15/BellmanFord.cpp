#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include "To_String.h"
#include <stdexcept>
#include "Graph.h"
#include <limits>
#include <stack>
#include "CostoMinimo.h"
#include <stdlib.h>
#include <iostream>

using namespace graph;
using namespace To_String;
using namespace costoMinimo;


void example()
{
    DGraphA<char>* g = new DGraphA<char>();
    Bellman<char>& bellman = Bellman<char>::getInstance();

    g->addNode('A');
    g->addNode('B');
    g->addNode('C');
    g->addNode('D');
    g->addNode('E');
    g->addNode('F');

    g->addEdge({'A','B'});
    g->addEdge({'A','C'});
    g->addEdge({'A','D'});

    g->addEdge({'B','E'});

    g->addEdge({'C','B'});
    g->addEdge({'C','E'});

    g->addEdge({'D','C'});
    g->addEdge({'D','F'});

    g->addEdge({'E','F'});

    std::map<std::tuple<char,char>,double> w;

    w[{'A','B'}] = 3;
    w[{'A','C'}] = 4;
    w[{'A','D'}] = 5;

    w[{'B','E'}] = -1;

    w[{'C','B'}] = -2;
    w[{'C','E'}] = 3;

    w[{'D','C'}] = -2;
    w[{'D','F'}] = -1;

    w[{'E','F'}] = 3;


    std::cout << ToString<Graph<char> >::show(g) << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << ToString<std::vector<char> >::show(bellman.getMinPath(g,&w,'A','F')) << std::endl;

}


int main(int argc, char const *argv[])
{
    example();
    return 0;
}
