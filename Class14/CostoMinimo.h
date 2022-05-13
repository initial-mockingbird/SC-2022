#pragma once
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
#include <iostream>
#include <queue>

#ifndef CostoMinimo_H // include guard
#define CostoMinimo_H

namespace costoMinimo
{
    using namespace To_String;
    using namespace graph;

    template <typename T>
    class CostoMinimo
    {
        public:
            virtual double getMinCost(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs,T s, T t);
            virtual std::vector<T>* getMinPath(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs, T s, T t);
        
            
    };

    template <typename T>
    class Bellman
    {
        public:
            static Bellman& getInstance()
            {
                static Bellman    instance; 
                                             
                return instance;
            }


            double getMinCost(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs,T s, T t)
            {
                std::map<T,double>* dist = new std::map<T,double>;
                std::map<T,T>* pred = new std::map<T,T>;
                bool b = bellmanFord(g,costs,s,dist,pred);

                if (!b)
                    throw std::domain_error( "Negative cycle detected!." );
                
                return (*dist)[t];
            }

            std::vector<T>* getMinPath(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs, T s, T t)
            {
                std::map<T,double>* dist = new std::map<T,double>;
                std::map<T,T>* pred = new std::map<T,T>;
                std::vector<T>* path = new std::vector<T>;
                std::stack<T> st;
                bool b = bellmanFord(g,costs,s,dist,pred);
                T v = t;
                if (!b)
                    throw std::domain_error( "Negative cycle detected!." );
                
                if ((*dist)[t] < std::numeric_limits<double>::infinity())
                {
                    st.push(v);
                    while (v != s)
                    {
                        v = (*pred)[v];
                        st.push(v);
                    }

                    while(!st.empty())
                    {
                        path->push_back(st.top());
                        st.pop();
                    }
                    
                }

                return path;
            }

            bool bellmanFord(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs,T s, std::map<T,double>* dist, std::map<T,T>* pred)
            {
                for(auto v : *(g->nodes()))
                    (*dist)[v] = std::numeric_limits<double>::infinity();
                

                (*dist)[s] = 0;
                (*pred)[s] = s;

                
                int totalV = g->nodes()->size();
                bool change = true;
                double c;
                for (size_t _ = 0; _ <= totalV; _++)
                {
                    if (!change)
                        break;
                    change = false;
                    for(auto e : *(g->edges()))
                    {   
                        auto [u,v] = *e;
                        c = (*dist)[u] + (*costs)[*e];
                        if (c < (*dist)[v])
                        {
                            change = true || change;
                            (*dist)[v] = c;
                            (*pred)[v] = u;

                        }
                    }
                }

                for(auto e : *(g->edges()))
                {
                    auto [u,v] = *e;
                    c = (*dist)[u] + (*costs)[*e];
                    if (c < (*dist)[v])
                        return false;
                }

                return true;
                
            }


        private:
            Bellman () {};
            Bellman (const Bellman&);
            Bellman& operator=(const Bellman&);

            

    };



    template <typename T>
    class Dijkstra
    {
        public:
            static Dijkstra& getInstance()
            {
                static Dijkstra    instance; 
                                             
                return instance;
            }

            std::vector<T>* getMinPath(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs, T s, T t)
            {
                std::map<T,double>* dist = new std::map<T,double>;
                std::map<T,T>* pred = new std::map<T,T>;
                std::vector<T>* path = new std::vector<T>;
                std::stack<T> st;
                dijkstra(g,costs,s,t,dist,pred);
                T v = t;
                
                if ((*dist)[t] < std::numeric_limits<double>::infinity())
                {
                    st.push(v);
                    while (v != s)
                    {
                        v = (*pred)[v];
                        st.push(v);
                    }

                    while(!st.empty())
                    {
                        path->push_back(st.top());
                        st.pop();
                    }
                    
                }

                return path;
            }

            void dijkstra(Graph<T>* g, std::map<std::tuple<T,T>,double>* costs,T s,T t, std::map<T,double>* dist, std::map<T,T>* pred)
            {
                std::set<T> visited;
                auto f = [](auto l, auto r){return std::get<0>(l) < std::get<0>(r);};
                std::priority_queue<std::tuple<double,T>, std::vector<std::tuple<double,T> >, decltype(f)>pq(f);
                double c;

                for(auto v : *(g->nodes()))
                    (*dist)[v] = std::numeric_limits<double>::infinity();
                

                (*dist)[s] = 0;
                (*pred)[s] = s;
                pq.push({0,s});

                while(!pq.empty())
                {
                    auto [_,u] = pq.top();
                    pq.pop();
                    if (visited.count(u) != 0)
                        continue;
                    
                    if (u == t)
                        return;
                    visited.insert(u);
                    
                    for(auto v : *(g->succs(u)))
                    {
                        c = (*dist)[u] + (*costs)[{u,v}];
                        if (c < (*dist)[v])
                        {
                            pq.push({c,v});
                            (*dist)[v] = c;
                            (*pred)[v] = u;
                        }
                    }
                }

            }
        private:
            Dijkstra () {};
            Dijkstra (const Dijkstra&);
            Dijkstra& operator=(const Dijkstra&);
    };

}; // namespace costoMinimo


#endif /* CostoMinimo_H */