/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_FRAME_HPP
#define MPG123XX_FRAME_HPP

#include <cstddef>
#include <cstdint>
#include <span>


namespace mpg123 {

    struct frame {

        std::uint32_t header = 0;
        std::span<std::byte> body;


        constexpr
        frame()
            noexcept = default;

        frame(unsigned long header,
              std::byte* data,
              std::size_t size)
            noexcept;


        frame(unsigned long header,
              char* data,
              std::size_t size)
            noexcept;

        frame(unsigned long header,
              unsigned char* data,
              std::size_t size)
            noexcept;

    }; // struct frame

} // namespace mpg123

#endif
