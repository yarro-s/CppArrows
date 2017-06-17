//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <cpp_arrows/arrow_base.h>
#include <arrow_base_test_helpers.h>
#include <functional>

using namespace arrow_base_testhelpers;
using namespace cpp_arrows;

TEST_CASE( "arrow_base constructor ", "[arrow_base constructor]" )
{
    const auto arr_mult2 = arrow_base<int, decltype(l_mult_by_2), int>(l_mult_by_2);
    REQUIRE( arr_mult2(10) == l_mult_by_2(10) );

    SomeStruct_ifl s1 {10, 154.35f, 3252652};
    auto s2 = s1;

    const auto arr_plus15_ref = arrow_base<SomeStruct_ifl&,
            decltype(l_plus15_ref), SomeStruct_ifl& >(l_plus15_ref);
    REQUIRE( arr_plus15_ref(s1) == l_plus15_ref(s2) );

    SomeClass_int some_class1_ref(25, 12);
    SomeClass_int some_class2_ref = some_class1_ref;
    SomeClass_int some_class1_bkp = some_class1_ref;

    const auto l_method3_ref = [](SomeClass_int& s)
    {
        (std::bind(&SomeClass_int::some_method3, &s))();
        return s;
    };
    const auto arr_method3_ref = arrow_base<SomeClass_int&,
            decltype(l_method3_ref), SomeClass_int&>(l_method3_ref);
    REQUIRE( arr_method3_ref(some_class1_ref) == l_method3_ref(some_class2_ref) );
    REQUIRE_FALSE( some_class1_ref == some_class1_bkp );
}

TEST_CASE( "make_arrow_base() and apply arrow on scalars", "[arrow_base make apply scalar]" )
{
    INFO("Arrow creation and application test with scalars");
    REQUIRE( (make_arrow_base<int>(l_via)(100))     == l_via(100) );
    REQUIRE( (make_arrow_base<int>(l_mult_by_2)(5)) == l_mult_by_2(5) );
    REQUIRE( (make_arrow_base<float>(l_plus_10p5)(5.2f))
                                               == l_plus_10p5(5.2f) );
    REQUIRE( (make_arrow_base<float>(l_div_by_5p5)(10.0f))
                                               == l_div_by_5p5(10.0f) );
    REQUIRE( (make_arrow_base<float>(l_div_by_3p2_trunc)(25.78f))
                                               == l_div_by_3p2_trunc(25.78f) );
    REQUIRE( (make_arrow_base<int>(l_div_int_by_7p7)(17))
                                               == l_div_int_by_7p7(17) );

    REQUIRE( (make_arrow_base<std::pair<int, int> >(l_pair_mult_by_5_and_3)
                 (std::make_pair(10, 12)))
                           == l_pair_mult_by_5_and_3(std::make_pair(10, 12)) );

    REQUIRE( (make_arrow_base<int>(&f_mult_by_2<int, int>)(5))
                                               == (f_mult_by_2<int, int>(5)) );
    REQUIRE( (make_arrow_base<int>(&f_plus_10p5<int, float>)(75.2))
                                          == (f_plus_10p5<int, float>(75.2)) );

    REQUIRE( arr_via(1001) == 1001);
    REQUIRE( arr_mult_by_2(arr_div_int_by_7p7(arr_plus_10p5(585)))
                          == l_mult_by_2(l_div_int_by_7p7(l_plus_10p5(585))) );
}

TEST_CASE( "make_arrow_base() and apply arrow on structs", "[arrow_base make apply structs]" )
{
    SomeStruct_ifl some_struct1{4, 5.35f, 64252};
    SomeStruct_ifl some_struct2 = some_struct1;

    INFO("Arrow creation and application test with structs");
    REQUIRE( arr_plus(some_struct1) == l_plus5(some_struct2) );
    REQUIRE( arr_minus(some_struct1) == l_minus7_5(some_struct2) );
    REQUIRE( arr_mult(some_struct1) == l_mult555(some_struct2) );

    auto arr_plus_const = make_arrow_base<SomeStruct_ifl &>(arr_plus);

    REQUIRE( arr_plus_const(some_struct1) == l_plus5(some_struct2) );

    const auto arr_plus15_ref_ = make_arrow_base<SomeStruct_ifl&>(l_plus15_ref);
    const auto some_struct1_bkp = some_struct1;

    REQUIRE( arr_plus15_ref_(some_struct1) == l_plus15_ref(some_struct2) );
    REQUIRE_FALSE( some_struct1_bkp == some_struct1 );
}

TEST_CASE( "make_arrow_base() and apply arrow on objects", "[arrow_base make apply objects]" )
{
    SomeClass_int some_class1(5, 2);
    SomeClass_int some_class2 = some_class1;

    auto arr_method1 = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method1);
    auto arr_method2 = make_arrow_base<SomeClass_int>(&SomeClass_int::some_method2);

    some_class2.some_method1();
    auto test_res1 = arr_method1(some_class1);

    INFO("Arrow creation and application test with classes");
    REQUIRE( test_res1 == some_class2 );

    some_class2.some_method2();
    auto test_res2 = arr_method2(test_res1);
    REQUIRE( test_res2 == some_class2 );

    SomeClass_int some_class3(45, 23);
    SomeClass_int some_class4 = some_class3;
    SomeClass_int some_class3_bkp = some_class3;

    const auto arr_method3_ref = make_arrow_base<SomeClass_int&>
            (&SomeClass_int::some_method3);

    some_class4.some_method3();
    REQUIRE( arr_method3_ref(some_class3) == some_class4 );
    REQUIRE_FALSE( some_class3 == some_class3_bkp );
}
