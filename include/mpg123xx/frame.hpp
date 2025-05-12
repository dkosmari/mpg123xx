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
        std::intmax_t num;
        std::span<const std::byte> samples;
    };

} // namespace mpg123

#endif
