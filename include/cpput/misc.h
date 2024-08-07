/**
    @file
    @author  Alexander Sherikov

    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief Various one-liners
*/

#ifndef H_CPPUT_MISC
#define H_CPPUT_MISC

/**
 * Sometimes it is not possible to omit name of an unused parameter, in such
 * cases this macro can be used to suppress compiler warnings about unused
 * parameters.
 */
#define CPPUT_UNUSED_ARG(parameter) (void)parameter;

#define CPPUT_MACRO_SUBSTITUTE(macro) macro

#define CPPUT_DISABLE_CLASS_COPY(Class)                                                                                \
public:                                                                                                                \
    Class(const Class &) = delete;                                                                                     \
    Class &operator=(const Class &) = delete;                                                                          \
    Class(Class &&) = delete;                                                                                          \
    Class &operator=(Class &&) = delete;

namespace cpput
{
    template <typename T>
    inline void ignoreResult(const T && /* unused result */)
    {
    }
}  // namespace cpput

#endif
