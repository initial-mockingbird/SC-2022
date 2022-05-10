#pragma once
#include <string>
#include <list>
#include <vector>
#include <tuple>

#ifndef TO_STRING_H // include guard
#define TO_STRING_H


namespace To_String
{
    template <typename T>
    class ToString
    {
        public:
            static const bool is_specialized = false;
            static std::string show(T);
    };

    template <>
    class ToString<int>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(int i){
            return std::to_string(i);
        }
    };

    template <>
    class ToString<float>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(float f){
            return std::to_string(f);
        }
    };

    template <>
    class ToString<double>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(double d){
            return std::to_string(d);
        }
    };

    template <>
    class ToString<long>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(long l){
            return std::to_string(l);
        }
    };

    template <>
    class ToString<std::string>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(std::string s){
            return s;
        }
    };

    
    template <>
    class ToString<char>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(char c){
            std::string ret = {c};
            return ret;
        }
    };

    template <>
    class ToString<bool>
    {
    public:
        static const bool is_specialized = true;
        static std::string show(bool b){
            if (b)
                return "true";
            return "false";
        }
    };
    

    template <typename T>
    class ToString<std::list<T> >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(std::list<T>* l)
        {   
            std::string res = "";
            for (auto c : *l)
                res += ToString<T>::show(c) + " -> ";
            
            return res + "nil";
        }
        static std::string show(std::list<T> l)
        {   
            std::string res = "";
            for (auto c : l)
                res += ToString<T>::show(c) + " -> ";
            
            return res + "nil";
        }
    };

    template <typename A, typename B>
    class ToString<std::tuple<A,B> >
    {
    public:
        static_assert(ToString<A>::is_specialized, "A does not have a ToString Class");
        static_assert(ToString<B>::is_specialized, "A does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(std::tuple<A,B>* t)
        {   
            if (t == NULL)
                return "NULL POINTER RECIEVED!";
            
            return ToString<std::tuple<A,B> >::show(*t);
        }
        static std::string show(std::tuple<A,B> t)
        {   
            const auto [first,second] = t;
            std::string res = "(";
            res += ToString<A>::show(first) + ", ";
            res += ToString<B>::show(second) + ")";
            
            return res;
        }
    };
    

    template <typename T>
    class ToString<std::vector<T> >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(std::vector<T>* l)
        {   
            if (l == NULL)
                return "NULL POINTER";
            return ToString<std::vector<T> >::show(*l);
        }
        static std::string show(std::vector<T> l)
        {   
            if (l.size() == 0)
                return "Nil";
            
            std::string res = "<";
            for (auto c : l)
                res += ToString<T>::show(c) + ", ";
            
            res.pop_back();
            res.pop_back();
            return res + ">";
        }
    };

    template <typename T>
    class ToString<std::vector<T>* >
    {
    public:
        static_assert(ToString<T>::is_specialized, "T does not have a ToString Class");
        static const bool is_specialized = true;
        static std::string show(std::vector<T>* l)
        {   
            if (l == NULL)
                return "NULL POINTER";
            return ToString<std::vector<T> >::show(*l);
        }
        static std::string show(std::vector<T> l)
        {   
            if (l.size() == 0)
                return "Nil";
            
            std::string res = "<";
            for (auto c : l)
                res += ToString<T>::show(c) + ", ";
            
            res.pop_back();
            res.pop_back();
            return res + ">";
        }
    };
}




#endif /* TO_STRING_H */