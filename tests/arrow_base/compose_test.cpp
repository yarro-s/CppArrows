//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <cpp_arrows/arrow_base.h>
#include <arrow_base_test_helpers.h>

using namespace arrow_base_testhelpers;

TEST_CASE( "Compose and apply scalar test", "[arrow_base scalar compose]" )
{
    INFO("Arrow composition test with scalars");
    REQUIRE( ((arr_mult_by_2 >> arr_plus_10p5)(100))
                            == (l_plus_10p5(l_mult_by_2(100))) );

    REQUIRE( ((arr_mult_by_2 >> arr_plus_10p5 >> arr_div_by_3p2_trunc)(15))
                            == (l_div_by_3p2_trunc(l_plus_10p5(l_mult_by_2(15)))) );
}

TEST_CASE( "Compose and apply struct test", "[arrow_base struct compose]" )
{
    SomeStruct_ifl some_struct1{44, 25.35f, 75146};
    SomeStruct_ifl some_struct2 = some_struct1;

    auto arr_plus_minus_mult = arr_plus >> arr_minus >> arr_mult;

    auto test_res = arr_plus_minus_mult(some_struct1);
    auto ref_res = l_mult555(l_minus7_5(l_plus5(some_struct2)));

    INFO("Arrow composition test with structs");
    REQUIRE( test_res.f1 == ref_res.f1 );
    REQUIRE( test_res.f2 == ref_res.f2 );
    REQUIRE( test_res.f3 == ref_res.f3 );
}

TEST_CASE( "Compose and apply class test", "[arrow_base class compose]" )
{
    SomeClass_int some_class1(5, 2);
    SomeClass_int some_class2 = some_class1;

    auto arr_method1  = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method1);
    auto arr_method2  = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method2);
    auto arr_method3  = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method3);
    auto arr_method123 = arr_method1 >> arr_method2 >> arr_method3;

    some_class2.some_method1();
    some_class2.some_method2();
    some_class2.some_method3();

    INFO("Arrow composition test with classes");
    REQUIRE( arr_method123(some_class1) == some_class2 );
}