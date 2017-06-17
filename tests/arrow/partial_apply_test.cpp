//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <make_arrow.h>
#include <arrow_test_helpers.h>
#include <utility>

const auto l_plus100 = [](int x)
{
    return x+100;
};

const auto arr_plus100 = cpp_arrows::make_arrow<int>(l_plus100);

const auto in  = std::make_pair<int, float>(10, 4143.5f);

TEST_CASE("Apply to first input", "[fst]")
{
    const auto res_fst = arr_plus100.fst<float>()(in);
    REQUIRE( res_fst.first  == l_plus100(10) );
    REQUIRE( res_fst.second == 4143.5f );
}

TEST_CASE("Apply to second input", "[snd]")
{
    const auto res_snd = arr_plus100.snd()(in);
    REQUIRE( res_snd.first == 10 );
    REQUIRE( res_snd.second == l_plus100(4143.5f) );
}
