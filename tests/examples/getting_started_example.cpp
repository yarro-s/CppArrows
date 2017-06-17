//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <iostream>
#include <cpp_arrows.hpp>

int main_ex()
{
    // make a simple arrow
    auto plus10 = cpp_arrows::make_arrow<int>(  // <int> is the type of the lambda param
            [](int x) { return x+10; });

    // make a couple more arrows
    auto mult55  = cpp_arrows::make_arrow<int>([](int x) { return x*55; });
    auto div10_8 = cpp_arrows::make_arrow<int>([](int x) { return (float)x/10.8f; });
    auto peek  = cpp_arrows::make_arrow<std::pair<int, float> >(
            [](std::pair<int, float> p)
            {
                std::cout << p.first << " | " << p.second << std::endl;
                return p;
            });
    auto sum_pair = cpp_arrows::make_arrow<std::pair<int, float> >(
            [](std::pair<int, float> p)
            {
                return p.first + p.second;
            });

    // compose these arrows into a computation
    auto composed_arrow = plus10 >> (mult55 & div10_8) >> peek >> sum_pair;

    // arrows can also be applied in the traditional way like functions
    auto composed_funcs = [=](int in)
    {
        int  res_plus = plus10(in);
        auto res_mult_div = std::make_pair(mult55(res_plus), div10_8(res_plus));
        return sum_pair(peek(res_mult_div));
    };

    // these are the same
    float res_1 = composed_arrow(55);
    float res_2 = composed_funcs(55);

    std::cout << "   Result with arrows: " << res_1 << " vs. "
              << "result with functions: " << res_2 << std::endl;
    return 0;
}

#include <catch.hpp>

TEST_CASE("Getting started example", "[getting started]")
{
    CHECK( main_ex() == 0 );
}
