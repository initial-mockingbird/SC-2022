#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include "To_String.h"
#include <stdexcept>


#ifndef Graph_H // include guard
#define Graph_H

namespace graph
{
    template <typename T>
    using edge = std::tuple<T,T>;

    template <typename T>
    class Graph
    {
        public:
            virtual std::vector<T>*   succs (T)     = 0;
            virtual std::vector<T>*   preds (T)     = 0;
            virtual std::vector<T>*   nodes ()      = 0;
            virtual std::vector<edge<T>*>* edges () = 0;
            virtual void addNode(T)                 = 0;
            virtual void addEdge(edge<T>)           = 0;
    };


    template <typename T>
    class DGraphA : public Graph<T>
    {
        public:

        DGraphA()
        {
            this->adjList = new std::map<T,std::vector<T>* >;
        }

        std::vector<T>* succs (T n)
        {
            return (*adjList)[n];
        }

        std::vector<T>* preds (T n)
        {
            std::vector<T>* ret = new std::vector<T>;

            for (const auto& [pred, succs] : *adjList)
            {
                if(elem(n,succs))
                    ret->push_back(pred);
            }

            return ret;

        }

        std::vector<T>* nodes ()
        {
            std::vector<T>* ret = new std::vector<T>;

            for (const auto& [pred, _] : *adjList)
                ret->push_back(pred);

            return ret;
        }

        std::vector<edge<T>*>* edges ()
        {
            std::vector<edge<T>*>* ret = new std::vector<edge<T>*>;

            for (const auto& [pred, succs] : *adjList)
            {
                for(auto succ : *succs)
                    ret->push_back(new std::tuple<T,T>(pred,succ));
            }

            return ret;
        }

        void addNode(T n)
        {
            if (!this->adjList->count(n))
                (*adjList)[n] = new std::vector<T>;
        }

        void addEdge(edge<T> e)
        {
            
            auto [p,q] = e;
            if (!adjList->count(p) || !adjList->count(q))
                throw std::domain_error( "A vertex does not belong to the graph." );
            
            if (!elem(q,(*adjList)[p]))
                (*adjList)[p]->push_back(q);
        }

        private:

        bool elem(T m, std::vector<T>* l)
        {
            for(auto var : *l)
            {
                if (m == var)
                    return true;
            }

            return false;
        }

        std::map<T,std::vector<T>* >* adjList;
    };

    template <typename T>
    class UDGraphA : public Graph<T>
    {
        public:

        UDGraphA()
        {
            this->adjList = new std::map<T,std::vector<T>* >;
        }

        std::vector<T>* succs (T n)
        {
            return (*adjList)[n];
        }

        std::vector<T>* preds (T n)
        {
            return this->succs(n);
        }

        std::vector<T>* nodes ()
        {
            std::vector<T>* ret = new std::vector<T>;

            for (const auto& [pred, _] : *adjList)
                ret->push_back(pred);

            return ret;
        }

        std::vector<edge<T>*>* edges ()
        {
            std::vector<edge<T>*>* ret = new std::vector<edge<T>*>;
            std::set<std::set<T> > seen = *new std::set<std::set<T> >;
            std::set<T> current = *new std::set<T>;

            for (const auto& [pred, succs] : *adjList)
            {
                current.insert(pred);
                for(auto succ : *succs)
                {
                    current.insert(succ);
                    if (!seen.count(current))
                        ret->push_back(new std::tuple<T,T>(pred,succ));
                    current.erase(succ);
                }
                current.erase(pred);
                    
            }

            return ret;
        }

        void addNode(T n)
        {
            if (!this->adjList->count(n))
                (*adjList)[n] = new std::vector<T>;
        }

        void addEdge(edge<T> e)
        {
            
            auto [p,q] = e;
            if (!adjList->count(p) || !adjList->count(q))
                throw std::domain_error( "A vertex does not belong to the graph." );
            if (!elem(q,(*adjList)[p]))
            {
                (*adjList)[p]->push_back(q);
                (*adjList)[q]->push_back(p);
            }
                
        }

        private:

        bool elem(T m, std::vector<T>* l)
        {
            for(auto var : *l)
            {
                if (m == var)
                    return true;
            }

            return false;
        }

        std::map<T,std::vector<T>* >* adjList;
    };
} // namespace name

namespace To_String
{
    using namespace graph;
    template <typename T>
    class ToString<Graph<T> >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(Graph<T>* g)
        {  
            std::string ret = "";
            for(auto node : *(g->nodes()))
            {   
                ret += ToString<T>::show(node);
                ret += " -> ";
                ret += ToString<std::vector<T> >::show(g->succs(node));
                ret += "\n";
            }

            
            return ret;
        }
    };
}

#endif /* Graph_H */