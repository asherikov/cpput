/**
    @file
    @author  Alexander Sherikov

    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief Deprecation macro
*/

#ifndef H_CPPUT_DEPRECATION
#define H_CPPUT_DEPRECATION

#ifdef __GNUC__

    #define CPPUT_DEPRECATED __attribute__((deprecated))

#else

    #define CPPUT_DEPRECATED

#endif

#endif
