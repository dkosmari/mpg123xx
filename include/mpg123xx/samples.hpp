/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_SAMPLES_HPP
#define MPG123XX_SAMPLES_HPP

#include <cstddef>
#include <cstdint>
#include <span>


namespace mpg123 {

    struct samples {

        std::intmax_t frame_num = 0;
        std::span<const std::byte> raw_data;


        constexpr
        samples()
            noexcept = default;

        samples(std::intmax_t num,
                const std::byte* data,
                std::size_t size)
            noexcept;

        samples(std::intmax_t num,
                const char* data,
                std::size_t size)
            noexcept;

        samples(std::intmax_t num,
                const unsigned char* data,
                std::size_t size)
            noexcept;


        template<typename T>
        [[nodiscard]]
        std::span<const T>
        as()
            const noexcept
        {
            return std::span<const T>{
                reinterpret_cast<const T*>(raw_data.data()),
                raw_data.size_bytes() / sizeof(T)
            };
        }

    }; // struct samples

} // namespace mpg123

#endif
