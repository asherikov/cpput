/**
    @file
    @author  Alexander Sherikov

    @brief
*/

#include <filesystem>
#include <cpput/concat.h>
#include "boost_utf_common.h"


// Arguments accepted by simple() and reserve():
//   string literals, char arrays, char pointers, const char pointers,
//   std::string (lvalue and rvalue), std::string_view.
//
// Single char, signed char, unsigned char, int and double are rejected at
// compile time by the static_assert in simple(), and at the call of .size()
// in reserve_strings(); this cannot be checked at runtime.
BOOST_AUTO_TEST_CASE(Concat)
{
    BOOST_REQUIRE_EQUAL("", cpput::concat::simple());
    BOOST_REQUIRE_EQUAL("", cpput::concat::reserve());
    BOOST_REQUIRE_EQUAL("", cpput::concat::reserve_strings());

    BOOST_REQUIRE_EQUAL("a", cpput::concat::simple("a"));
    BOOST_REQUIRE_EQUAL("a", cpput::concat::reserve("a"));

    BOOST_REQUIRE_EQUAL("abc", cpput::concat::simple("a", "b", "c"));
    BOOST_REQUIRE_EQUAL("abc", cpput::concat::reserve("a", "b", "c"));

    const std::filesystem::path path = "/usr/lib/sendmail.cf";
    BOOST_REQUIRE_EQUAL("/tmp/usr/lib/sendmail.cf", cpput::concat::simple("/tmp", path));

    const std::string first = "In ";
    const std::string expected = first + __func__ + "() // message";
    BOOST_REQUIRE_EQUAL(expected, cpput::concat::simple(first, __func__, "() // ", "message"));
    BOOST_REQUIRE_EQUAL(expected, cpput::concat::simple("In ", __func__, "() // ", std::string("message")));
    BOOST_REQUIRE_EQUAL(expected, cpput::concat::reserve(first, __func__, "() // ", "message"));

    const std::string left = "left";
    const std::string right = "right";
    BOOST_REQUIRE_EQUAL("leftright", cpput::concat::simple(left, right));
    BOOST_REQUIRE_EQUAL("leftright", cpput::concat::simple(left, std::string("right")));
    BOOST_REQUIRE_EQUAL("leftright", cpput::concat::simple(std::string("left"), right));
    BOOST_REQUIRE_EQUAL("leftright", cpput::concat::reserve(left, right));

    const std::string_view view = "view";
    BOOST_REQUIRE_EQUAL("viewview", cpput::concat::simple(view, std::string_view("view")));
    BOOST_REQUIRE_EQUAL("viewview", cpput::concat::reserve(view, std::string_view("view")));

    char char_array[] = "array";
    char *mutable_pointer = char_array;
    const char *const_pointer = char_array;
    BOOST_REQUIRE_EQUAL("array", cpput::concat::simple(char_array));
    BOOST_REQUIRE_EQUAL("array", cpput::concat::simple(mutable_pointer));
    BOOST_REQUIRE_EQUAL("array", cpput::concat::simple(const_pointer));
    BOOST_REQUIRE_EQUAL("array", cpput::concat::reserve(char_array));

    BOOST_REQUIRE_EQUAL(
            "literal arrayarray left view",
            cpput::concat::simple("literal ", char_array, mutable_pointer, " ", left, " ", view));
    BOOST_REQUIRE_EQUAL(
            "literal arrayarray left view",
            cpput::concat::reserve("literal ", char_array, mutable_pointer, " ", left, " ", view));
    BOOST_REQUIRE_EQUAL(
            "literal arrayarray left view",
            cpput::concat::reserve_strings(
                    std::string_view("literal "),
                    std::string_view(char_array),
                    std::string_view(mutable_pointer),
                    std::string_view(" "),
                    left,
                    std::string_view(" "),
                    view));

    BOOST_REQUIRE_EQUAL("abab", cpput::concat::reserve_strings(std::string_view("ab"), std::string_view("ab")));
}
