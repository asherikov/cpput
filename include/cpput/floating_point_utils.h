/**
    @file
    @author  Alexander Sherikov

    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief NaN and infinity checks, loosely based on
        https://github.com/opencv/opencv/blob/3.0.0/modules/hal/include/opencv2/hal/defs.h
*/


#ifndef H_CPPUT_FP_UTILS
#define H_CPPUT_FP_UTILS

#include <stdint.h>
#include <string.h>

namespace cpput
{
    inline bool isNaN(const double value)
    {
        uint64_t raw;
        memcpy(&raw, &value, sizeof(double));
        return (((uint32_t)(raw >> 32) & 0x7fffffff) + ((uint32_t)raw != 0) > 0x7ff00000);
    }


    inline bool isInfinity(const double value)
    {
        uint64_t raw;
        memcpy(&raw, &value, sizeof(double));
        return (((uint32_t)(raw >> 32) & 0x7fffffff) == 0x7ff00000 && (uint32_t)raw == 0);
    }


    inline bool isNaN(const float value)
    {
        uint32_t raw;
        memcpy(&raw, &value, sizeof(float));
        return ((raw & 0x7fffffff) > 0x7f800000);
    }


    inline bool isInfinity(const float value)
    {
        uint32_t raw;
        memcpy(&raw, &value, sizeof(float));
        return ((raw & 0x7fffffff) == 0x7f800000);
    }
}  // namespace cpput

#endif
