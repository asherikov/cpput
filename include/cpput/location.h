/**
    @file
    @author  Alexander Sherikov
    @copyright 2019 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#ifndef H_CPPUT_LOCATION
#define H_CPPUT_LOCATION

#include <cstddef>

namespace cpput
{
    /**
     * @brief Location of a data chunk (offset + length).
     */
    class Location
    {
    public:
        std::size_t offset_;
        std::size_t length_;


    public:
        /**
         * @brief Constructor
         */
        Location()
        {
            set(0, 0);
        }


        /**
         * @brief Construct location with given parameters
         *
         * @param[in] offset offset
         * @param[in] length length
         */
        Location(const std::size_t offset, const std::size_t length)
        {
            set(offset, length);
        }


        /**
         * @brief Compare two locations
         *
         * @param[in] another_location some other location
         *
         * @return true/false
         */
        bool operator==(const Location &another_location) const
        {
            return ((offset_ == another_location.offset_) && (length_ == another_location.length_));
        }


        /**
         * @brief Compare two locations
         *
         * @param[in] another_location some other location
         *
         * @return true/false
         */
        bool operator!=(const Location &another_location) const
        {
            return (!(*this == another_location));
        }


        /**
         * @brief Check length of location
         *
         * @param[in] max_length maximal length
         *
         * @return true if location is valid
         */
        bool checkLength(const std::size_t max_length) const
        {
            return ((offset_ <= end()) && (end() <= max_length));
        }


        /**
         * @brief Offset of the first element
         *
         * @return offset of the first element (offset_)
         */
        std::size_t front() const
        {
            return (offset_);
        }


        /**
         * @brief Offset of the element following the last element
         *
         * @return offset of the element following the last element (offset_ + length_)
         */
        std::size_t end() const
        {
            return (offset_ + length_);
        }


        /**
         * @brief Set location.
         *
         * @param[in] offset offset
         * @param[in] length length
         */
        void set(const std::size_t offset, const std::size_t length)
        {
            offset_ = offset;
            length_ = length;
        }
    };
}  // namespace cpput

#endif
