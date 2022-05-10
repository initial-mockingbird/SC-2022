#pragma once
#include <string>
#include <list>

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

    /*
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
    */

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

            // [1,2,3,4]
            // 1 -> 2 -> 3 -> 4 -> nil
            std::string res = "";
            for (auto c : l)
                res += ToString<T>::show(c) + " -> ";
            
            return res + "nil";
        }
    };
}




#endif /* TO_STRING_H */