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


enum class WType {BabyFace,Heel};


WType switchType (WType t)
{
    if (t == WType::BabyFace)
        return WType::Heel;

    if (t == WType::Heel)
        return WType::BabyFace;
    
    throw std::domain_error( "Enumeration Error" );
}

namespace To_String
{
    template <>
    class ToString<WType>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(WType t)
        {  
            if (t == WType::BabyFace)
                return "BabyFace";
            if (t == WType::Heel)
                return "Heel";
            
            throw std::domain_error( "Enumeration Error" );
        }
    };
}


template <typename T>
bool bfs(UDGraphA<T>* _g, UDGraphA<std::tuple<WType,T> >* g)
{
    WType parentType   = WType::BabyFace;
    WType childrenType = switchType(parentType);
    std::vector<T> current;
    std::vector<T> next   ;
    std::set<T> visited;
    std::map<T,WType> assocs;
    std::tuple<WType,T> tu;
    std::tuple<WType,T> tv;


    for(auto s : *(_g->nodes()))
    {
        if (visited.count(s) != 0)
            continue;
        
        current.push_back(s);
        visited.insert(s);
                
        assocs[s] = parentType;
        g->addNode(*new std::tuple<WType,T>(parentType,s));
        

        while (current.size() > 0)
        {
            for(auto u : current)
            {
                assocs[u] = parentType;
                tu = *new std::tuple<WType,T>(parentType,u);


                childrenType = switchType(parentType);

                for(auto v : *(_g->succs(u)))
                {
                    if (assocs.count(v)!=0 && assocs[v] != childrenType)
                    {   std::cout << "u: " << ToString<T>::show(u) << ", " << ToString<WType>::show(parentType) << std::endl;
                        std::cout << "v: " << ToString<T>::show(v) << ", " << ToString<WType>::show(childrenType) << std::endl;
                        std::cout << ToString<Graph<std::tuple<WType,T> > >::show(g) << std::endl;
                        return false;
                    }
                        
                    
                    if (visited.count(v) == 0)
                    {
                        visited.insert(v);
                        next.push_back(v);
                        assocs[v] = childrenType;
                        tv = *new std::tuple<WType,T>(childrenType,v);
                        g->addNode(tv);
                        g->addEdge(*new std::tuple<std::tuple<WType,T>,std::tuple<WType,T> >(tu,tv));
                    }
                }
            }
            parentType = childrenType;

            current.swap(next);
            next.clear();
        }
    }

    return true;
}

template <typename T>
bool sol(std::vector<T> wrestlers,std::vector<std::tuple<T,T> > rivalries,UDGraphA<std::tuple<WType,T> >* g)
{
    UDGraphA<T>* _g = new UDGraphA<T>();

    for(auto w : wrestlers)
        _g->addNode(w);
    
    for(auto e : rivalries)
        _g->addEdge(e);
    
    return bfs(_g,g);
    

}

void hasSol()
{
    UDGraphA<std::tuple<WType,char> >* g = new UDGraphA<std::tuple<WType,char> >;
    std::vector<char> wrestlers = {'A','B','C','D','E'};
    std::vector<std::tuple<char,char> > rivalries = 
        { *new std::tuple<char,char>('A','B')
        , *new std::tuple<char,char>('A','C')
        , *new std::tuple<char,char>('B','D')
        , *new std::tuple<char,char>('C','D')
        };


    bool b = sol(wrestlers,rivalries,g);

    std::cout << ToString<bool>::show(b) << std::endl;
    std::cout << ToString<Graph<std::tuple<WType,char> > >::show(g) << std::endl;
}

void noSol()
{
    UDGraphA<std::tuple<WType,char> >* g = new UDGraphA<std::tuple<WType,char> >;
    std::vector<char> wrestlers = {'A','B','C','D'};
    std::vector<std::tuple<char,char> > rivalries = 
        { *new std::tuple<char,char>('A','B')
        , *new std::tuple<char,char>('A','C')
        , *new std::tuple<char,char>('B','D')
        , *new std::tuple<char,char>('C','D')
        , *new std::tuple<char,char>('B','C')
        };


    bool b = sol(wrestlers,rivalries,g);

    std::cout << ToString<bool>::show(b) << std::endl;
    //std::cout << ToString<Graph<std::tuple<WType,char> > >::show(g) << std::endl;
}


int main(int argc, char const *argv[])
{
    /*DGraphA<char>* cycle = cyclicGraph();
    DGraphA<char>* noCycle = nonCyclicGraph();
    */
    hasSol();
    std::cout << "--------------------------" << std::endl;
    noSol();
    std::cout << "RAN" << std::endl;
    return 0;
}