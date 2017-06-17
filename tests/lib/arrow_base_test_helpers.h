//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#ifndef CPPARROWS_ARROW_BASE_HELPERS_H
#define CPPARROWS_ARROW_BASE_HELPERS_H

#include <cpp_arrows/arrow_base.h>
#include <utility>
#include <iostream>

namespace arrow_base_testhelpers
{
    using namespace cpp_arrows;

    const auto l_via = [](int x) { return x; };
    const auto l_mult_by_2 = [](int x) { return x * 2; };
    const auto l_plus_10p5 = [](float y) { return y + 10.5f; };
    const auto l_div_by_5p5 = [](float z) { return z / 5.5f; };
    const auto l_div_int_by_7p7 = [](int z) { return z / 7.7f; };
    const auto l_div_by_3p2_trunc = [](float x) { return (int) (x / 3.2f); };
    const auto l_pair_mult_by_5_and_3 = [](std::pair<int, int> p) {
        auto res = std::make_pair(p.first * 5, p.second / 3);
        return res.first + res.second;
    };

    template<typename In, typename Out>
    Out f_mult_by_2(In x) {
        return x * 2;
    }

    template<typename In, typename Out>
    Out f_plus_10p5(In x) {
        return x + 10.5f;
    }

    template<typename In, typename Out>
    Out f_div_by_5p5(In z) {
        return z / 5.5f;
    }

    const auto arr_via = cpp_arrows::make_arrow_base<int>(l_via);
    const auto arr_mult_by_2 = cpp_arrows::make_arrow_base<int>(l_mult_by_2);
    const auto arr_plus_10p5 = cpp_arrows::make_arrow_base<float>(l_plus_10p5);
    const auto arr_div_by_5p5 = cpp_arrows::make_arrow_base<float>(l_div_by_5p5);
    const auto arr_div_int_by_7p7
            = cpp_arrows::make_arrow_base<int>(l_div_int_by_7p7);

    const auto arr_div_by_3p2_trunc
            = cpp_arrows::make_arrow_base<float>(l_div_by_3p2_trunc);
    const auto arr_sum_i_i
            = cpp_arrows::make_arrow_base<std::pair<int, int> >(
                    [](std::pair<int, int> p) {
                        return p.first + p.second;
                    });
    const auto arr_sum_i_f
            = cpp_arrows::make_arrow_base<std::pair<int, float> >(
                    [](std::pair<int, float> p) {
                        return p.first + p.second;
                    });
    const auto arr_pair_mult_by_5_and_3
            = cpp_arrows::make_arrow_base<std::pair<int, int>>(l_pair_mult_by_5_and_3);
}

namespace arrow_base_testhelpers
{
    template <typename Field1, typename Field2, typename Field3>
    struct SomeStruct{
        Field1 f1;
        Field2 f2;
        Field3 f3;

        bool operator==(const SomeStruct &rhs) const {
            return f1 == rhs.f1 &&
                   f2 == rhs.f2 &&
                   f3 == rhs.f3;
        }

        bool operator!=(const SomeStruct &rhs) const {
            return !(rhs == *this);
        }
    };

    template <typename Field1, typename Field2, typename Field3>
    void print_some_struct(SomeStruct<Field1, Field2, Field3>& s)
    {
        std::cout << " - {" << s.f1 << ", " << s.f2 << ", " << s.f3 << "}" << std::endl;
    }

    using SomeStruct_ifl = struct SomeStruct<int, float, long>;

    auto l_plus5 = [](SomeStruct_ifl s)
    {
        s.f1 += 5;
        return s;
    };
    auto l_minus7_5 = [](SomeStruct_ifl s)
    {
        s.f2 -= 7.5f;
        return s;
    };
    auto l_mult555 = [](SomeStruct_ifl s)
    {
        s.f3 *= 555;
        return s;
    };
    auto l_plus15_ref = [](SomeStruct_ifl& s)
    {
        s.f1 += 15;
        return s;
    };

    auto arr_plus = make_arrow_base<SomeStruct_ifl>(l_plus5);
    auto arr_minus = make_arrow_base<SomeStruct_ifl>(l_minus7_5);
    auto arr_mult = make_arrow_base<SomeStruct_ifl>(l_mult555);
}

namespace arrow_base_testhelpers
{
    template<typename In, typename Out1, typename Out2>
    class SomeClass {
    public:
        SomeClass(Out1 prop1, Out2 prop2) : prop1(prop1), prop2(prop2) {}

        Out1 some_method1() {
            prop1 -= prop2;
            return prop1;
        }

        Out2 some_method2() {
            prop2 += prop1;
            return prop2;
        }

        Out2 some_method3() {
            prop2 *= prop1;
            prop1 -= prop1;
            return prop2;
        }

        bool operator==(const SomeClass &rhs) const {
            return prop1 == rhs.prop1 && prop2 == rhs.prop2;
        }

        bool operator!=(const SomeClass &rhs) const {
            return !(rhs == *this);
        }
    private:
        Out1 prop1;
        Out2 prop2;
    };

    using SomeClass_int  = SomeClass<int, int, int>;
}

#endif //CPPARROWS_ARROW_BASE_HELPERS_H
