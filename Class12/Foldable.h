#pragma once
#include <functional>

#ifndef FOLDABLE_H // include guard
#define FOLDABLE_H

namespace FoldableM
{
    template < template<typename A> class C, typename A, typename B>
    class Foldable
    {
    public:
        static const bool is_specialized = false;
        static B fold(std::function<B(B,A)>, B, C<A>*);
        static int length(C<A>* t);
        static A   min(C<A>* t);
        static A   max(C<A>* t);
        static std::list<A>* toList(C<A>* t);
    };
}

#endif /* FOLDABLE_H */