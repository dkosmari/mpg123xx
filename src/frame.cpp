/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
#include "mpg123xx/frame.hpp"

namespace mpg123 {


    frame::frame(std::intmax_t num,
                 const std::byte* data,
                 std::size_t size)
        noexcept :
        num{num},
        samples{data, size}
    {}


    frame::frame(std::intmax_t num,
                 const char* data,
                 std::size_t size)
        noexcept :
        num{num},
        samples{reinterpret_cast<const std::byte*>(data), size}
    {}


    frame::frame(std::intmax_t num,
                 const unsigned char* data,
                 std::size_t size)
        noexcept :
        num{num},
        samples{reinterpret_cast<const std::byte*>(data), size}
    {}

} // namespace mpg123
