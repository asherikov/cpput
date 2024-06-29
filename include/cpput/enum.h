/**
    @file
    @author  Alexander Sherikov

    @copyright 2022 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include "better_enum.h"

// clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"  // doesnt seem to work (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53431)
#define CPPUT_ENUM(name, ...) BETTER_ENUM(name, int, UNDEFINED=0, __VA_ARGS__)  // NOLINT
#pragma GCC diagnostic pop
// clang-format on
