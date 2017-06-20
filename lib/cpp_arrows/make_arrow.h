//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#ifndef CPPARROWS_MAKE_ARROW_H
#define CPPARROWS_MAKE_ARROW_H

#include <vector>
#include <functional>
#include <type_traits>
#include <arrow.h>

namespace cpp_arrows
{
    /** Creates an `arrow` from a lambda or a callable class that implements `operator()`.
      * @tparam In The input type of the the underlying lambda or callable class.
      * @tparam Callable  Inferred type of the underlying lambda or callable class.
      * @tparam Out Inferred return type of the underlying callable.
      * @param call The lambda or callable that implements the computation.
      * @return A new arrow that accepts values of type In as its input
      * and returns values of type Out as its output.
      */
    template<typename In, class Callable> inline
    auto make_arrow(Callable call)
    {
        return arrow<In, decltype(call), decltype(&Callable::operator())>(call);
    }

    /** Creates an arrow from a function.
      * @tparam In The input type of the the underlying function.
      * @tparam Lambda  Inferred type of the underlying function.
      * @tparam Out Inferred return type of the underlying function.
      * @param func A pointer to the function that implements
      * the computation.
      * @return A new arrow that accepts values of type In as its input
      * and returns values of type Out as its output.
      */
    template<typename In, typename Out> inline
    auto make_arrow(Out (*func)(In))
    {
        const auto lambda_f = [=](In in)
        {
            return func(in);
        };
        return make_arrow<In>(lambda_f);
    }

    /** Creates an arrow from a class method.
      * @tparam MethodOwnerClass The class that is the owner of the method.
      * @tparam Out Inferred return type of the method.
      * @param func A pointer to the class method that implements
      * the computation.
      * @return A new arrow that accepts instances of MethodOwnerClass class
      * as its input and returns the instances with the class method applied.
      */
    template<typename MethodOwnerClass, typename Out> inline
    auto make_arrow(Out (MethodOwnerClass::*method)())
    {
        auto applicable_method = std::mem_fn(method);
        return arrow<MethodOwnerClass&, decltype(applicable_method),
                Out>(applicable_method);
    }
}

#endif //CPPARROWS_MAKE_ARROW_H
