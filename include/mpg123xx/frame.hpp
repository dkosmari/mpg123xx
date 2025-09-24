/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_FRAME_HPP
#define MPG123XX_FRAME_HPP

#include <cstdint>
#include <span>


namespace mpg123 {

    struct frame {

        std::intmax_t num = 0;
        std::span<const std::byte> samples;


        constexpr
        frame()
            noexcept = default;

        frame(std::intmax_t num,
              const std::byte* data,
              std::size_t size)
            noexcept;

        frame(std::intmax_t num,
              const char* data,
              std::size_t size)
            noexcept;

        frame(std::intmax_t num,
              const unsigned char* data,
              std::size_t size)
            noexcept;

    };

} // namespace mpg123

#endif
