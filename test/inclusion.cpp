/**
    @file
    @author  Alexander Sherikov

    @brief
*/

#define CPPUT_TRACE_ENABLE
#include <cpput/all.h>
#include "boost_utf_common.h"


BOOST_AUTO_TEST_CASE(Inclusion)
{
    cpput::setSignalHandler(handleSignal, { SIGINT, SIGTERM });
    cpput::print_backtrace();
    BOOST_REQUIRE(true);
}
