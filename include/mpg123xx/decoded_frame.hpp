/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_DECODED_FRAME_HPP
#define MPG123XX_DECODED_FRAME_HPP

#include <cstddef>
#include <cstdint>
#include <span>


namespace mpg123 {

    struct decoded_frame {

        std::intmax_t num = 0;
        std::span<const std::byte> samples;


        constexpr
        decoded_frame()
            noexcept = default;

        decoded_frame(std::intmax_t num,
                      const std::byte* data,
                      std::size_t size)
            noexcept;

        decoded_frame(std::intmax_t num,
                      const char* data,
                      std::size_t size)
            noexcept;

        decoded_frame(std::intmax_t num,
                      const unsigned char* data,
                      std::size_t size)
            noexcept;

    }; // struct decoded_frame

} // namespace mpg123

#endif
