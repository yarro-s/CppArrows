//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <make_arrow.h>
#include <arrow_test_helpers.h>
#include <utility>

using namespace arrow_test_helpers;

const auto l_mult10 = [](int x)
{
    return x*10;
};
const auto l_plus25 = [](int x)
{
    return x+25;
};
const auto l_div5_7 = [](int x)
{
    return (float)(x/5.7f);
};
const auto l_plus3_8 = [](float x)
{
    return (float)(x+3.8f);
};
const auto l_pack_struct = [](int x)
{
    B_struct res {x*5, x+15, std::to_string(x)+"!!!"};
    return res;
};

const auto arr_mult = cpp_arrows::make_arrow<int>(l_mult10);
const auto arr_plus = cpp_arrows::make_arrow<int>(l_plus25);

TEST_CASE("Arrow >> composition", "[operator>>]")
{
    auto in(552);

    const auto arr_mult_plus = arr_mult >> arr_plus;
    REQUIRE( arr_mult_plus(in) == l_plus25(l_mult10(in)) );

    const auto arr_div = cpp_arrows::make_arrow<int>(l_div5_7);
    const auto arr_div_mult_plus = arr_div >> arr_mult >> arr_plus;

    REQUIRE( arr_div_mult_plus(in) == l_plus25(l_mult10(l_div5_7(in))) );

    const auto arr_pack = cpp_arrows::make_arrow<int>(l_pack_struct);

    const auto full_conveyor = arr_mult_plus >> arr_div_mult_plus >> arr_mult
                                             >> arr_pack;
    REQUIRE( full_conveyor(in) ==
        l_pack_struct(l_mult10(l_plus25(l_mult10(l_div5_7(l_plus25(l_mult10(in))))))) );
}

TEST_CASE("Arrow * composition", "[operator*]")
{
    const auto arr_plus_f = cpp_arrows::make_arrow<float>(l_plus3_8);
    const auto arr_mult_plus_f = arr_mult * arr_plus_f;

    const auto in_1 = std::make_pair(10, 24.54f);
    const std::pair<int, float> in_2 = in_1;

    const auto res_arr_mult_plus_f = arr_mult_plus_f(in_1);
    REQUIRE( res_arr_mult_plus_f.first  == l_mult10(in_2.first) );
    REQUIRE( res_arr_mult_plus_f.second == l_plus3_8(in_2.second) );
}

TEST_CASE("Arrow & composition", "[operator&]")
{
    const auto arr_mult_plus_f = arr_mult & l_plus25;

    const auto in = 2425;
    const auto res_arr_mult_plus_f = arr_mult_plus_f(in);
    const auto res_mult_plus_f = std::make_pair(l_mult10(in), l_plus25(in));

    REQUIRE( res_arr_mult_plus_f.first  == res_mult_plus_f.first );
    REQUIRE( res_arr_mult_plus_f.second == res_mult_plus_f.second );
}


