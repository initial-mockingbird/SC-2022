#include "Graph.h"
#include <vector>
#include <tuple>
#include <map>
#include "To_String.h"
#include <stdlib.h>
#include <iostream>
#include <set>

using namespace graph;
using namespace To_String;



template <typename T>
void _dfs(Graph<T>* g, T s, std::set<T>* visited, int* counter,std::map<T,int>* open,std::map<T,int>* close)
{
    if (visited->count(s) != 0)
        return ;

    visited->insert(s);
    (*open)[s] = *counter;
    *counter += 1;

    for(auto v : *(g->succs(s)))
        _dfs(g,v,visited,counter,open,close);

    (*close)[s] = *counter;

    
}


template <typename T>
bool hasCycle(DGraphA<T>* g)
{

    std::set<std::tuple<bool,T> >* visited  = new std::set<std::tuple<bool,T> >;
    std::map<std::tuple<bool,T>,int>* open  = new std::map<std::tuple<bool,T>,int>;
    std::map<std::tuple<bool,T>,int>* close = new std::map<std::tuple<bool,T>,int>;
    T aux;
    DGraphA<std::tuple<bool,T> >* _g = new DGraphA<std::tuple<bool,T>>();

    for(auto node : *(g->nodes()))
    {
        aux = node;
        _g->addNode(*new std::tuple<bool,T>(true,node));
    }

    std::tuple<bool,T> source = *new std::tuple<bool,T>(false,aux);
    _g->addNode(source);

    for (auto e : *(g->edges()))
    {
        const auto& [u,v] = *e;
        std::tuple<bool,T> _u = *new std::tuple<bool,T>(true,u);
        std::tuple<bool,T> _v = *new std::tuple<bool,T>(true,v);
        std::tuple<std::tuple<bool,T>,std::tuple<bool,T> > _e = *new std::tuple<std::tuple<bool,T>,std::tuple<bool,T> >(_u,_v);
        _g->addEdge(_e);
    }

    for(auto node : *(g->nodes()))
    {
        std::tuple<bool,T> _node = *new std::tuple<bool,T>(true,node);
        std::tuple<std::tuple<bool,T>,std::tuple<bool,T> > e = *new std::tuple<std::tuple<bool,T>,std::tuple<bool,T> >(source,_node);
        _g->addEdge(e);
    }

    std::cout << ToString<Graph<std::tuple<bool,T> > >::show(_g) << std::endl;

    int counter = 0;
    _dfs(_g,source,visited,&counter,open,close);

    for (auto e : *(_g->edges()))
    {
        const auto& [_u,_v] = *e;
        const auto [bu,_1] = _u;
        const auto [bv,_2] = _v;

        if ((*open)[_v] <= (*open)[_u] && (*close)[_u] <= (*close)[_v] )
            return true;
    }


    return false;
}

DGraphA<char>* cyclicGraph()
{
    DGraphA<char>* g = new DGraphA<char>();
    

    g->addNode('A');
    g->addNode('B');
    g->addNode('C');
    g->addNode('D');
    g->addNode('E');
    g->addNode('F');
    g->addNode('G');
    g->addNode('H');

    g->addEdge(*new std::tuple<int,int>('A','B'));
    g->addEdge(*new std::tuple<int,int>('B','F'));
    g->addEdge(*new std::tuple<int,int>('B','E'));
    g->addEdge(*new std::tuple<int,int>('C','D'));
    g->addEdge(*new std::tuple<int,int>('D','H'));
    g->addEdge(*new std::tuple<int,int>('E','A'));
    g->addEdge(*new std::tuple<int,int>('F','C'));
    g->addEdge(*new std::tuple<int,int>('F','G'));
    g->addEdge(*new std::tuple<int,int>('G','C'));
    g->addEdge(*new std::tuple<int,int>('G','D'));
    g->addEdge(*new std::tuple<int,int>('H','G'));


    std::cout << ToString<Graph<char> >::show(g) << std::endl;

    return g;
}

DGraphA<char>* nonCyclicGraph()
{
    DGraphA<char>* g = new DGraphA<char>();
    

    g->addNode('A');
    g->addNode('B');
    g->addNode('C');
    g->addNode('D');
    g->addNode('E');
    g->addNode('F');
    g->addNode('G');
    g->addNode('H');

    //g->addEdge(*new std::tuple<int,int>('A','B'));
    g->addEdge(*new std::tuple<int,int>('B','F'));
    g->addEdge(*new std::tuple<int,int>('B','E'));
    g->addEdge(*new std::tuple<int,int>('C','D'));
    g->addEdge(*new std::tuple<int,int>('D','H'));
    g->addEdge(*new std::tuple<int,int>('E','A'));
    g->addEdge(*new std::tuple<int,int>('F','C'));
    g->addEdge(*new std::tuple<int,int>('F','G'));
    g->addEdge(*new std::tuple<int,int>('G','C'));
    g->addEdge(*new std::tuple<int,int>('G','D'));
    //g->addEdge(*new std::tuple<int,int>('H','G'));


    std::cout << ToString<Graph<char> >::show(g) << std::endl;

    return g;
}


int main(int argc, char const *argv[])
{
    DGraphA<char>* cycle = cyclicGraph();
    DGraphA<char>* noCycle = nonCyclicGraph();
    

    std::cout << hasCycle(cycle) << std::endl;
    std::cout << hasCycle(noCycle) << std::endl;
    
    std::cout << "RAN" << std::endl;
    return 0;
}