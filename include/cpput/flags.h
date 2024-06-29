/**
    @file
    @author  Alexander Sherikov

    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.

    @brief
*/

#pragma once

#ifndef H_CPPUT_FLAGS
#define H_CPPUT_FLAGS

namespace cpput
{
    template <typename t_Integer, class t_Derived>
    class Flags
    {
    public:
        enum Action
        {
            DEFAULT = 0,
            REPLACE = 1,
            SET = 2,
            UNSET = 3
        };


    public:
        t_Integer flags_;


    public:
        void initialize(const t_Integer flags, const Action action_type = REPLACE)
        {
            switch (action_type)
            {
                case REPLACE:
                    replace(flags);
                    break;

                case SET:
                    static_cast<t_Derived *>(this)->setDefaults();
                    set(flags);
                    break;

                case UNSET:
                    static_cast<t_Derived *>(this)->setDefaults();
                    unset(flags);
                    break;

                default:
                    CPPUT_THROW("Unknown Flags::Action type.");
            }
        }


        void copy(const t_Derived &from, const t_Integer mask)
        {
            set(from.flags_ & mask);
        }

        bool isSet(const t_Integer flags) const
        {
            return (flags_ & flags);
        }

        void replace(const t_Integer flags)
        {
            flags_ = flags;
        }

        void set(const t_Integer flags)
        {
            flags_ |= flags;
        }

        void unset(const t_Integer flags)
        {
            flags_ &= ~flags;
        }
    };
}  // namespace cpput

#endif
