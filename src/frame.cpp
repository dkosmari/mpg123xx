/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "mpg123xx/frame.hpp"


namespace mpg123 {

    frame::frame(unsigned long header,
                 std::byte* data,
                 std::size_t size)
        noexcept :
        header{static_cast<std::uint32_t>(header)},
        body{data, size}
    {}


    frame::frame(unsigned long header,
                 char* data,
                 std::size_t size)
        noexcept :
        header{static_cast<std::uint32_t>(header)},
        body{reinterpret_cast<std::byte*>(data), size}
    {}


    frame::frame(unsigned long header,
                 unsigned char* data,
                 std::size_t size)
        noexcept :
        header{static_cast<std::uint32_t>(header)},
        body{reinterpret_cast<std::byte*>(data), size}
    {}

} // namespace mpg123
