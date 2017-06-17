//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#ifndef CPPARROWS_MAKE_ARROW_BASE_H
#define CPPARROWS_MAKE_ARROW_BASE_H

#include <functional>
#include <type_traits>

namespace cpp_arrows
{
    template<typename In, class F, typename Out>
    class arrow_base;

    /**
     * Creates an arrow from a callable, i.e. a function, lambda or a
     * class that implements `operator()`).
     * @tparam In The input type of the the underlying callable.
     * @tparam Lambda  Inferred type of the underlying callable.
     * @tparam Out Inferred return type of the underlying callable.
     * @param l The callable that actually implements the computation.
     * @return A new arrow that accepts values of type In as its input
     * and return values of type Out as its output.
     */
    template<typename In, class Lambda> inline
    auto make_arrow_base(Lambda l)
    {
        return arrow_base<In, decltype(l), decltype(&Lambda::operator())>(l);
    }

    template<typename In, typename Out> inline
    auto make_arrow_base(Out (*f)(In))
    {
        const auto lambda_f = [&f](In in)
        {
            return f(in);
        };
        return make_arrow_base<In, decltype(lambda_f)>(lambda_f);
    }

    template<typename FOwnerClass, typename Out> inline
    auto make_arrow_base(Out (std::remove_reference<FOwnerClass>::type::*method)())
    {
        const auto m_bound = [&method](FOwnerClass owner)
        {
            (std::bind(method, &owner))();
            return owner;
        };
        return make_arrow_base<FOwnerClass>(m_bound);
    }
}

#endif //CPPARROWS_MAKE_ARROW_BASE_H
