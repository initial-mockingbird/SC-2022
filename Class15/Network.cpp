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
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

using namespace graph;
using namespace To_String;
using namespace costoMinimo;


void example()
{
    DGraphA<int>* g = new DGraphA<int>();
    Bellman<int>& bellman = Bellman<int>::getInstance();

    g->addNode(1);
    g->addNode(2);
    g->addNode(3);
    g->addNode(4);

    g->addEdge({2,1});
    g->addEdge({2,3});
    g->addEdge({3,4});


    std::map<std::tuple<int,int>,double> w;
    std::map<int,double>* dist = new std::map<int,double>;
    std::map<int,int>* pred = new std::map<int,int>;
    w[{2,1}] = 1;
    w[{2,3}] = 1;
    w[{3,4}] = 1;


    std::cout << ToString<Graph<int> >::show(g) << std::endl;
    std::cout << "-------------------------------" << std::endl;

    bellman.bellmanFord(g,&w,2,dist,pred);

    double ans = 0;

    for(auto [u,c] : *dist)
    {   
        ans = MAX(ans,c);   
    }

    std::cout << ans << std::endl;


}


int main(int argc, char const *argv[])
{
    example();
    return 0;
}
