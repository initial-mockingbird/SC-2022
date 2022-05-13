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

template <typename T>
std::vector<std::vector<T> >* paths(Graph<T>* g,T u,T v, int k)
{
    std::vector<std::vector<T> >* ret = new std::vector<std::vector<T> >;


    if (k == 0 && u == v)
    {
        ret->push_back({v});
        return ret;
    }
    
    if (k <= 0) 
        return {};
    

    std::cout << "u: " << u << ", v: " << v << ", k: " << k << std::endl;

    for(auto _u : *(g->succs(u)))
    {
        std::cout << "succ: " << _u << std::endl;
        std::vector<std::vector<T> >* ps = paths(g,_u,v,k-1);
        if (ps == NULL)
            continue;
        for(auto p : *ps)
        {   
            p.push_back(u);
            ret->push_back(p);
        }
            
    }
    return ret;
}

template <typename T>
void sol(Graph<T>* g,std::map<std::tuple<T,T>,double>* costs,T u,T v, int k)
{
    std::vector<std::vector<T> >* ps = paths( g, u, v, k);

    auto f = [costs](std::vector<T> p)
    {
        double c = 0;
        for (size_t i = 0; i < p.size() - 1; i++)
            c += (*costs)[{p[i+1],p[i]}];
        return c;
    };

    double minSoFar = std::numeric_limits<double>::infinity();
    std::vector<T> minPSoFar;
    double c;
    for(auto p : *ps)
    {
        c = f(p);
        if(c < minSoFar)
        {
            c = minSoFar;
            minPSoFar = p;
        }
    }

    std::cout << ToString<std::vector<T> >::show(minPSoFar) << std::endl;

}
void example()
{
    DGraphA<int>* g = new DGraphA<int>();

    g->addNode(0);
    g->addNode(1);
    g->addNode(2);
    g->addNode(3);


    g->addEdge({0,1});

    g->addEdge({1,2});
    g->addEdge({1,3});

    g->addEdge({2,0});
    g->addEdge({2,3});



    std::map<std::tuple<int,int>,double> w;

    std::vector<std::tuple<int,int,double> > aux;

    aux.push_back({0,1,100});

    aux.push_back({1,2,100});
    aux.push_back({1,3,600});

    aux.push_back({2,0,100});
    aux.push_back({2,3,200});

    for(auto [u,v,p] : aux)
    {
        w[{u,v}] = p;
    }


    std::cout << ToString<Graph<int> >::show(g) << std::endl;
    std::cout << "-------------------------------" << std::endl;
    sol(g,&w,0,3,2);

}


int main(int argc, char const *argv[])
{
    example();
    return 0;
}
