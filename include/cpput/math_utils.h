/**
    @file
    @author  Alexander Sherikov
    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#ifndef H_CPPUT_MATH
#define H_CPPUT_MATH

#include <cmath>

namespace cpput
{
    namespace math
    {
        //========================================================================
        // Constants
        //========================================================================
        /// PI constant
        const double g_pi = 3.14159265358979323846;


        //========================================================================
        // Math
        //========================================================================

        /**
         * @brief Returns true if the difference between two given variables is
         * below the given tolerance.
         *
         * @param[in] var1
         * @param[in] var2
         * @param[in] tol
         *
         * @return true / false
         */
        inline bool isApproximatelyEqual(const double var1, const double var2, const double tol)
        {
            return (std::abs(var1 - var2) < tol);
        }


        //========================================================================
        // Geometry
        //========================================================================

        /**
         * @brief Convert degrees to radians
         *
         * @param[in] degrees degrees
         *
         * @return radians
         */
        inline double convertDegreesToRadians(const double degrees)
        {
            return (g_pi * degrees / 180);
        }


        /**
         * @brief Convert radians to degrees
         *
         * @param[in] radians
         *
         * @return degrees
         */
        inline double convertRadiansToDegrees(const double radians)
        {
            return (radians * 180 / g_pi);
        }
    }  // namespace math
}  // namespace cpput

#endif
