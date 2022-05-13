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
    UDGraphA<char>* g = new UDGraphA<char>();
    Dijkstra<char>& dijkstra = Dijkstra<char>::getInstance();

    g->addNode('A');
    g->addNode('B');
    g->addNode('C');
    g->addNode('D');
    g->addNode('E');
    g->addNode('F');

    g->addEdge({'A','B'});
    g->addEdge({'A','C'});
    g->addEdge({'A','D'});

    g->addEdge({'B','C'});
    g->addEdge({'B','D'});
    g->addEdge({'B','E'});

    g->addEdge({'C','D'});
    g->addEdge({'C','E'});
    g->addEdge({'C','F'});

    g->addEdge({'D','E'});
    g->addEdge({'D','F'});

    g->addEdge({'E','F'});

    std::map<std::tuple<char,char>,double> w;

    std::vector<std::tuple<char,char,double> > aux;

    aux.push_back({'A','B',3});
    aux.push_back({'A','C',5});
    aux.push_back({'A','S',9});

    aux.push_back({'B','C',3});
    aux.push_back({'B','D',4});
    aux.push_back({'B','E',7});

    aux.push_back({'C','D',2});
    aux.push_back({'C','E',6});
    aux.push_back({'C','F',8});

    aux.push_back({'D','E',2});
    aux.push_back({'D','F',2});

    aux.push_back({'E','F',5});

    for(auto [u,v,p] : aux)
    {
        w[{u,v}] = p;
        w[{v,u}] = p;
    }


    std::cout << ToString<Graph<char> >::show(g) << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << ToString<std::vector<char> >::show(dijkstra.getMinPath(g,&w,'A','F')) << std::endl;

}


int main(int argc, char const *argv[])
{
    example();
    return 0;
}
