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
std::vector<T>* bfs(Graph<T>* g, T s)
{
    std::vector<T>* ret    = new std::vector<T>;
    std::vector<T> current;
    std::vector<T> next   ;
    std::set<T> visited;

    current.push_back(s);
    visited.insert(s);
    ret->push_back(s);

    while (current.size() > 0)
    {
        for(auto u : current)
        {
            for(auto v : *(g->succs(u)))
            {
                if (visited.count(v) == 0)
                {
                    visited.insert(v);
                    next.push_back(v);
                    ret->push_back(v);
                }
                
            }
        }
        current.swap(next);
        next.clear();
    }

    return ret;
}

template <typename T>
std::vector<std::vector<T>*>* bfsLevels(Graph<T>* g, T s)
{
    std::vector<std::vector<T>*>* ret    = new std::vector<std::vector<T>*>;
    std::vector<T> current;
    std::vector<T> next   ;
    std::set<T> visited;

    current.push_back(s);
    visited.insert(s);
    ret->push_back(new std::vector<T>(current));

    while (current.size() > 0)
    {
        for(auto u : current)
        {
            for(auto v : *(g->succs(u)))
            {
                if (visited.count(v) == 0)
                {
                    visited.insert(v);
                    next.push_back(v);
                }
                
            }
        }
        current.swap(next);
        ret->push_back(new std::vector<T>(current));
        next.clear();
    }

    return ret;
}


template <typename T>
void _dfs(Graph<T>* g, T s, std::vector<T>* ret, std::set<T>* visited)
{
    if (visited->count(s) != 0)
        return ;

    visited->insert(s);
    ret->push_back(s);

    for(auto v : *(g->succs(s)))
        _dfs(g,v,ret,visited);
    
}


template <typename T>
std::vector<T>* dfs(Graph<T>* g, T s)
{
    std::vector<T>* ret  = new std::vector<T>;
    std::set<T>* visited = new std::set<T>;
    _dfs(g,s,ret,visited);

    return ret;
}



int main(int argc, char const *argv[])
{
    
    Graph<char>* g = new DGraphA<char>();
    

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

    std::cout << ToString<std::vector<char> >::show(bfs(g,'B')) << std::endl;
    std::cout << ToString<std::vector<std::vector<char>*> >::show(bfsLevels(g,'B')) << std::endl;


    std::cout << ToString<std::vector<char> >::show(dfs(g,'B')) << std::endl;
    
    std::cout << "RAN" << std::endl;
    return 0;
}