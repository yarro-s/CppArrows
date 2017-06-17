//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#ifndef CPPARROWS_ARROW_H
#define CPPARROWS_ARROW_H

#include <arrow_base.h>

namespace cpp_arrows
{
    template<typename In, class Lambda> inline
    auto make_arrow(Lambda call);

    /** `arrow` wraps a computation defined by some underlying function, labmda or class
      * method (which is commonly refered to as _callable_). Arrows are normally created
      * by the `cpp_arrows::make_arrow` function with the callable and the type of the
      * input argument of the callable.
      * @see `cpp_arrows::make_arrow`
      */
    template<typename In, class F, typename Out>
    class arrow : public arrow_base<In, F, Out>
    {
    public:
        arrow(const F& f) : arrow_base<In, F, Out>(f) {}
        arrow(const arrow<In, F, Out>& a) : arrow_base<In, F, Out>(a) {}

        template<class Arrow_adjacent>
        auto operator*(const Arrow_adjacent& a_j) const
        {
            using Composed_input = std::pair<In, typename Arrow_adjacent::In_type>;
            auto f_composed = [this, &a_j](Composed_input in)
            {
                return std::make_pair(this->operator()(in.first), a_j(in.second));
            };
            return make_arrow<Composed_input>(f_composed);
        }

        template<class Arrow_adjacent>
        auto operator&(const Arrow_adjacent& a_j) const
        {
            auto f_composed = [this, &a_j](In in)
            {
                return std::make_pair(arrow_base<In, F, Out>::apply(in), a_j(in));
            };
            return make_arrow<In>(f_composed);
        }
    };
}

#endif //CPPARROWS_ARROW_H
