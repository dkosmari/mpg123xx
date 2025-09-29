/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "mpg123xx/samples.hpp"


namespace mpg123 {

    samples::samples(std::intmax_t num,
                     const std::byte* data,
                     std::size_t size)
        noexcept :
        frame_num{num},
        raw_data{data, size}
    {}


    samples::samples(std::intmax_t num,
                     const char* data,
                     std::size_t size)
        noexcept :
        frame_num{num},
        raw_data{reinterpret_cast<const std::byte*>(data), size}
    {}


    samples::samples(std::intmax_t num,
                     const unsigned char* data,
                     std::size_t size)
        noexcept :
        frame_num{num},
        raw_data{reinterpret_cast<const std::byte*>(data), size}
    {}

} // namespace mpg123
