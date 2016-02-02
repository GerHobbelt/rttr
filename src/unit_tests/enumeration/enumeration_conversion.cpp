/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014, 2015 - 2016 Axel Menzel <info@rttr.org>                     *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#include <rttr/registration>

using namespace rttr;
using namespace std;

#include <iostream>
#include <memory>
#include <functional>

#include <catch/catch.hpp>

enum class access
{
    read = 1,
    write = 2,
    exec = 4
};


/////////////////////////////////////////////////////////////////////////////////////////

RTTR_REGISTRATION
{
    registration::enumeration<access>("access")
    (
        value("read",    access::read),
        value("write",   access::write),
        value("exec", access::exec)
    );
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("enumeration - value_to_name()", "[enumeration]")
{
    enumeration e = type::get_by_name("access").get_enumeration();

    CHECK(e.value_to_name(access::read)     == "read");
    CHECK(e.value_to_name(access::write)    == "write");
    CHECK(e.value_to_name(access::exec)     == "exec");

    // negative
    e = type::get_by_name("access_unknown").get_enumeration();
    CHECK(e.value_to_name(access::read).empty() == true);
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("enumeration - name_to_value()", "[enumeration]")
{
    enumeration e = type::get_by_name("access").get_enumeration();

    REQUIRE(e.name_to_value("read").is_type<access>()   == true);
    REQUIRE(e.name_to_value("write").is_type<access>()  == true);
    REQUIRE(e.name_to_value("write").is_type<access>()  == true);

    CHECK(e.name_to_value("read").get_value<access>()   == access::read);
    CHECK(e.name_to_value("write").get_value<access>()  == access::write);
    CHECK(e.name_to_value("exec").get_value<access>()   == access::exec);

    // negative
    e = type::get_by_name("access_unknown").get_enumeration();
    REQUIRE(e.name_to_value("write").is_type<access>() == false);
}

/////////////////////////////////////////////////////////////////////////////////////////