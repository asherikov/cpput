/**
    @file
    @author  Alexander Sherikov

    @copyright 2022 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include <memory>

namespace cpput
{
    template <class t_Self, class... t_Bases>
    class PtrAddon : public t_Bases...
    {
    public:
        using Ptr = std::shared_ptr<t_Self>;
        using ConstPtr = std::shared_ptr<const t_Self>;

        template <class... t_Args>
        static Ptr makePtr(t_Args &&...args)
        {
            return std::make_shared<t_Self>(std::forward<t_Args>(args)...);
        }
    };
}  // namespace
