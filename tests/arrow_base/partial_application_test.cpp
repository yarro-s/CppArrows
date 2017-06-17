//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <cpp_arrows/arrow_base.h>
#include <arrow_base_test_helpers.h>

using namespace arrow_base_testhelpers;

TEST_CASE( "Partial scalar application test", "[arrow_base partial scalar application]" )
{
    INFO("Arrow partial application test with scalars");
    REQUIRE( ( (arr_mult_by_2.fst() >> arr_sum_i_i)(std::make_pair(10, 777)) )
                                        == l_mult_by_2(10) + 777 );
    REQUIRE( ( (arr_mult_by_2.snd() >> arr_sum_i_i)(std::make_pair(5579, 15)) )
                                        == 5579 + l_mult_by_2(15) );

    REQUIRE( ( (int)(arr_plus_10p5.fst() >> arr_sum_i_f)(std::make_pair(7.8f, 555)) )
                                        == (int)(l_plus_10p5(7.8f)+555) );
    REQUIRE( ( (int)(arr_plus_10p5.snd() >> arr_sum_i_f)(std::make_pair(587, 2.7)) )
                                        == (int)(l_plus_10p5(2.7f)+587) );
}

TEST_CASE( "Partial struct application test", "[arrow_base partial struct application]" )
{
    SomeStruct_ifl some_struct1{44, 25.35f, 75146};
    SomeStruct_ifl some_struct2 = some_struct1;

    const auto fst_app_arg = std::make_pair(some_struct1, some_struct2);
    const auto fst_app_res = arr_plus.fst()(fst_app_arg);

    INFO("Arrow partial application test with structs");
    REQUIRE( fst_app_res.first  == arr_plus(some_struct1) );
    REQUIRE( fst_app_res.second == some_struct2 );
    REQUIRE_FALSE( fst_app_res.second == fst_app_res.first );

    const auto snd_app_arg = std::make_pair(some_struct1, some_struct2);
    const auto snd_app_res = arr_plus.snd()(snd_app_arg);

    REQUIRE( snd_app_res.first  == some_struct2 );
    REQUIRE( snd_app_res.second == arr_plus(some_struct1) );
    REQUIRE_FALSE( snd_app_res.second == snd_app_res.first );
}

TEST_CASE( "Partial class application test", "[arrow_base partial class application]" )
{
    SomeClass_int some_class1(5, 2);
    SomeClass_int some_class2 = some_class1;

    const auto arr_method1 = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method1);
    const auto fst_app_arg = std::make_pair(some_class1, some_class2);
    const auto fst_app_res = arr_method1.fst()(fst_app_arg);

    INFO("Arrow partial application test with classes");
    REQUIRE( fst_app_res.first  == arr_method1(some_class1) );
    REQUIRE( fst_app_arg.second == fst_app_res.second );
    REQUIRE_FALSE( fst_app_res.first == fst_app_res.second );

    const auto snd_app_arg = std::make_pair(some_class1, some_class2);
    const auto snd_app_res = arr_method1.snd()(snd_app_arg);

    REQUIRE( snd_app_res.second  == arr_method1(some_class1) );
    REQUIRE( snd_app_arg.first   == snd_app_res.first );
    REQUIRE_FALSE( snd_app_res.first == snd_app_res.second );
}

