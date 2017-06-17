//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <CppArrows/cpp_arrows.hpp>
#include <catch.hpp>
#include <iostream>


TEST_CASE("Creating and composing arrows quick example", "[make_arrow]")
{
    using namespace cpp_arrows;
    auto a = 1+2;
    // Define some operations with arrows
    const auto op_plus = make_arrow<int>([](int x) { return x+10; }); // <int> is the input type of the lambda
    const auto op_div  = make_arrow<int>([](int x) { return x/1.5f; });
    const auto op_mult = make_arrow<float>([](float x) { return x*2.42255f; });
    const auto op_acc  = make_arrow<std::pair<float, float> >(
            [](std::pair<float, float> p)
            {
                return p.first+p.second;
            });

    const auto op_composed = op_plus >> (op_div & op_mult) >> op_acc;

    const float res1 = op_composed(55);

    // Arrows can also be viewed as usual functions.
    // The following function application is equivalent to the code above
    const float res2 = op_acc(std::make_pair(op_div(op_plus(55)),
                                             op_mult(op_plus(55))));
    // res1 == res2 at this point
    if (res1 == res2) std::cout << "All good" << std::endl;
    else std::cout << "WRONG RESULT: res1 == "<< res1
                   << " vs. res2 == " << res2 << std::endl;

    CHECK(res1 == res2);
}
