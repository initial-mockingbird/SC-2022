#include "Graph.h"
#include <vector>
#include <tuple>
#include <map>
#include "To_String.h"
#include <stdlib.h>
#include <iostream>

using namespace graph;
using namespace To_String;


int main(int argc, char const *argv[])
{
    
    Graph<int>* g = new DGraphA<int>();

    g->addNode(0);
    g->addNode(1);
    g->addNode(2);
    g->addNode(3);

    g->addEdge(*new std::tuple<int,int>(0,1));
    g->addEdge(*new std::tuple<int,int>(0,3));
    g->addEdge(*new std::tuple<int,int>(1,1));
    g->addEdge(*new std::tuple<int,int>(1,2));
    g->addEdge(*new std::tuple<int,int>(3,0));

    std::cout << ToString<Graph<int> >::show(g) << std::endl;

    std::cout << "RAN" << std::endl;
    return 0;
}

