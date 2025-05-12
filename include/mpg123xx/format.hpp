/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_FORMAT_HPP
#define MPG123XX_FORMAT_HPP

#include <iosfwd>
#include <string>

#include <fmt123.h>


namespace mpg123 {

    [[nodiscard]]
    constexpr
    unsigned
    sample_size(mpg123_enc_enum encoding)
        noexcept
    {
        return MPG123_SAMPLESIZE(encoding);
    }


    [[nodiscard]]
    constexpr
    unsigned
    sample_size(unsigned encoding)
        noexcept
    {
        return MPG123_SAMPLESIZE(encoding);
    }


    struct format {
        long rate;
        unsigned channels; // bitset from mpg123_channelcount
        unsigned encoding; // bitset from mpg123_enc_enum
    };


    std::string
    to_string(const format& fmt);


    std::ostream&
    operator <<(std::ostream& out,
                const format& fmt);

} // namespace mpg123

#endif
