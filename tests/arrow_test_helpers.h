//
// Created by Yar Sh.
// Copyright (c) 2017 Yar Sh.
// MIT License. See LICENCE for more details.
//

#ifndef CPPARROWS_ARROW_TEST_HELPERS_H
#define CPPARROWS_ARROW_TEST_HELPERS_H

#include <string>

namespace arrow_test_helpers
{
    struct A_struct_type
    {
        int int_val;
        float float_val;
        long long extra_long_val;

        bool operator==(const A_struct_type &rhs) const
        {
            return int_val == rhs.int_val &&
                   float_val == rhs.float_val &&
                   extra_long_val == rhs.extra_long_val;
        }

        bool operator!=(const A_struct_type &rhs) const
        {
            return !(rhs == *this);
        }
    };
    typedef struct A_struct_type A_struct;

    struct B_struct_type
    {
        int int_val1;
        int int_val2;
        std::string str1;

        bool operator==(const B_struct_type &rhs) const
        {
            return int_val1 == rhs.int_val1 &&
                   int_val2 == rhs.int_val2 &&
                   str1 == rhs.str1;
        }

        bool operator!=(const B_struct_type &rhs) const
        {
            return !(rhs == *this);
        }
    };
    typedef struct B_struct_type B_struct;
}

namespace arrow_test_helpers
{
    class A_class
    {
    public:
        int method_A1()
        {
            x += 15;
            return x;
        }

        float method_A2()
        {
            y *= 2.5f;
            return y;
        }

        A_class(int x, float y) : x(x), y(y) {}

        bool operator==(const A_class &rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const A_class &rhs) const
        {
            return !(rhs == *this);
        }

    private:
        int x;
        float y;
    };

    class B_class
    {
    public:
        long method_B1()
        {
            z *= 4526;
            return z;
        }

        double method_B2()
        {
            k /= 346.52f;
            return k;
        }

    private:
        long z;
        double k;
    };
}

#endif //CPPARROWS_ARROW_TEST_HELPERS_H
