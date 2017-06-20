//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <make_arrow.h>
#include <arrow_test_helpers.h>


TEST_CASE("Arrow creation and application on scalars by values", "[make_arrow]")
{
    const auto l_plus5 = [](int x)
    {
        return x + 5;
    };
    const auto arr_plus5 = cpp_arrows::make_arrow<int>(l_plus5);
    REQUIRE( arr_plus5(10) == l_plus5(10) );

    const auto l_plus5_byref = [](int& x)
    {
        x += 5;
        return x;
    };
    const auto arr_plus5_byref = cpp_arrows::make_arrow<int&>(l_plus5_byref);

    auto arg_x_1(145);
    auto arg_x_2 = arg_x_1;
    const auto arg_x_copy = arg_x_1;

    REQUIRE( arr_plus5_byref(arg_x_1) == l_plus5_byref(arg_x_2) );
    REQUIRE_FALSE( arg_x_1 == arg_x_copy );
}


TEST_CASE("Arrow creation and application on scalars by reference", "[make_arrow]")
{
    const auto l_plus5_byref = [](int& x)
    {
        x += 5;
        return x;
    };
    const auto arr_plus5_byref = cpp_arrows::make_arrow<int&>(l_plus5_byref);

    auto arg_x_1(145);
    auto arg_x_2 = arg_x_1;
    const auto arg_x_copy = arg_x_1;

    REQUIRE( arr_plus5_byref(arg_x_1) == l_plus5_byref(arg_x_2) );
    REQUIRE_FALSE( arg_x_1 == arg_x_copy );
}

using namespace arrow_test_helpers;

TEST_CASE("Arrow creation and application on structs by values", "[make_arrow]")
{
    const auto l_change_A = [](A_struct a_struct)
    {
        a_struct.int_val += 53;
        a_struct.float_val /= 2.53f;
        a_struct.extra_long_val *= 64763;
        return a_struct;
    };
    const auto arr_change_A = cpp_arrows::make_arrow<A_struct>(l_change_A);

    auto arg_A_struct_1 = A_struct{14, 45.256f, 98642};
    auto arg_A_struct_2 = arg_A_struct_1;
    const auto arg_A_struct_copy = arg_A_struct_1;

    REQUIRE( arr_change_A(arg_A_struct_1) == l_change_A(arg_A_struct_2) );
    REQUIRE( arg_A_struct_1 == arg_A_struct_copy );
    REQUIRE( arg_A_struct_2 == arg_A_struct_copy );
}

TEST_CASE("Arrow creation and application on structs by reference", "[make_arrow]")
{
    const auto l_change_A_byref = [](A_struct& a_struct)
    {
        a_struct.int_val += 423;
        a_struct.float_val /= 3.4253f;
        a_struct.extra_long_val *= 751323;
        return a_struct;
    };
    const auto arr_change_A_byref =
            cpp_arrows::make_arrow<A_struct&>(l_change_A_byref);

    auto arg_A_struct_1 = A_struct{354, 55.16f, 3632};
    auto arg_A_struct_2 = arg_A_struct_1;
    const auto arg_A_struct_copy = arg_A_struct_1;

    REQUIRE( arr_change_A_byref(arg_A_struct_1) == arr_change_A_byref(arg_A_struct_2) );
    REQUIRE_FALSE( arg_A_struct_1 == arg_A_struct_copy );
    REQUIRE_FALSE( arg_A_struct_2 == arg_A_struct_copy );
    REQUIRE( arg_A_struct_1 == arg_A_struct_2 );
}

TEST_CASE("Arrow creation and application on classes by value", "[make_arrow]")
{
    const auto arr_change_A_obj =
            cpp_arrows::make_arrow<A_class>(&A_class::method_A2);

    A_class arg_A_obj_1(865, 82.518f);
    A_class arg_A_obj_2 = arg_A_obj_1;
    const auto arg_A_obj_copy = arg_A_obj_1;

    arg_A_obj_2.method_A2();
    arr_change_A_obj(arg_A_obj_1);
    REQUIRE( arg_A_obj_1 == arg_A_obj_2 );
    REQUIRE_FALSE( arg_A_obj_1 == arg_A_obj_copy );
}

