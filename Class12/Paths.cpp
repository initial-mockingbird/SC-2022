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
int dfs(DGraphA<T>* g,std::map<T,int>* mem,T s, T t)
{
    if (s==t)
    {
        (*mem)[t]=1;
        return 1;
    }

    if (mem->count(s) > 0)
        return (*mem)[s];

    int count = 0;
    for(auto v : *(g->succs(s)))
    {
        if (mem->count(v) == 0) 
            dfs(g,mem,v,t);

        count += (*mem)[v];
    }

    (*mem)[s] = count;
    return count;
}



void example()
{
    DGraphA<char>* g = new DGraphA<char>;

    for (char c = 'a'; c <= 'n'; c++)
        g->addNode(c);
    
    g->addEdge(*new std::tuple<char,char>('a','e'));
    g->addEdge(*new std::tuple<char,char>('a','f'));
    g->addEdge(*new std::tuple<char,char>('a','e'));

    g->addEdge(*new std::tuple<char,char>('b','e'));
    g->addEdge(*new std::tuple<char,char>('b','i'));
    g->addEdge(*new std::tuple<char,char>('b','c'));

    g->addEdge(*new std::tuple<char,char>('c','f'));
    g->addEdge(*new std::tuple<char,char>('c','j'));
    g->addEdge(*new std::tuple<char,char>('c','g'));

    g->addEdge(*new std::tuple<char,char>('d','c'));
    g->addEdge(*new std::tuple<char,char>('d','g'));
    g->addEdge(*new std::tuple<char,char>('d','n'));

    g->addEdge(*new std::tuple<char,char>('e','h'));

    g->addEdge(*new std::tuple<char,char>('f','i'));
    g->addEdge(*new std::tuple<char,char>('f','m'));

    g->addEdge(*new std::tuple<char,char>('g','f'));

    
    g->addEdge(*new std::tuple<char,char>('i','h'));

    g->addEdge(*new std::tuple<char,char>('j','l'));
    g->addEdge(*new std::tuple<char,char>('j','k'));

    g->addEdge(*new std::tuple<char,char>('k','n'));


    g->addEdge(*new std::tuple<char,char>('m','j'));


    std::cout << dfs(g,new std::map<char,int>,'d','j') << std::endl;
    std::cout << dfs(g,new std::map<char,int>,'c','j') << std::endl;
    std::cout << dfs(g,new std::map<char,int>,'e','j') << std::endl;
}


int main(int argc, char const *argv[])
{
    example();
    std::cout << "RAN" << std::endl;
    return 0;
}