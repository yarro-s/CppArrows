//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#include <catch.hpp>
#include <make_arrow.h>
#include <arrow_test_helpers.h>

using namespace arrow_test_helpers;

TEST_CASE("Apply arrows with type conversions on scalars" "[apply]")
{
    auto l_int_to_float = [](int x)
    {
        return (float)x / 5.62f;
    };
    const auto arr_int_to_float = cpp_arrows::make_arrow<int>(l_int_to_float);

    auto arg_x_1(586);
    auto arg_x_2 = arg_x_1;

    REQUIRE( arr_int_to_float(arg_x_1) == Approx(l_int_to_float(arg_x_1)) );
}

TEST_CASE("Apply arrows with type conversions on structs" "[apply]")
{
    auto l_A_to_B_struct = [](A_struct a_struct)
    {
        a_struct.int_val += 345;
        a_struct.float_val /= 3.673f;
        a_struct.extra_long_val *= 5262;

        B_struct b_struct
                {
                        (int)(a_struct.extra_long_val / a_struct.int_val),
                        (int)(a_struct.float_val * a_struct.int_val / 2),
                        std::to_string(a_struct.extra_long_val+a_struct.int_val
                                       +a_struct.float_val)
                };
        return b_struct;
    };
    const auto arr_A_to_B_struct =
            cpp_arrows::make_arrow<A_struct>(l_A_to_B_struct);

    A_struct arg_A_struct_1{ 36, 56.5345f, 3574737 };
    auto arg_A_struct_2 = arg_A_struct_1;

    REQUIRE( arr_A_to_B_struct(arg_A_struct_1) == l_A_to_B_struct(arg_A_struct_2) );
}

