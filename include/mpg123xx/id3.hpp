/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_ID3_HPP
#define MPG123XX_ID3_HPP

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <mpg123.h>


namespace mpg123 {

    struct id3v1 {

        std::string  title;
        std::string  artist;
        std::string  album;
        std::string  year;
        std::string  comment;
        std::uint8_t track = 0; // only for ID3v1.1
        std::uint8_t genre = 0;


        constexpr
        id3v1()
            noexcept = default;

        id3v1(const mpg123_id3v1* src);

    }; // struct id3v1


    struct text {
        std::string lang;
        std::string id;
        std::string description;
        std::string data;

        constexpr
        text()
            noexcept = default;


        text(const mpg123_text* src);

        text(const mpg123_text& src);

    }; // struct text

    struct picture {
        mpg123_id3_pic_type type;
        std::string description;
        std::string mime_type;
        std::vector<std::byte> data;
    }; // struct picture


    struct id3v2 {

        std::uint8_t version;
        std::string title;
        std::string artist;
        std::string album;
        std::string year;
        std::string genre;
        std::string comment;

        std::vector<text> comments;
        std::vector<text> texts;
        std::vector<text> extras;
        std::vector<picture> pictures;


        constexpr
        id3v2()
            noexcept = default;

        id3v2(const mpg123_id3v2* src);

    }; // struct id3v2


    struct id3 {
        std::optional<id3v1> v1;
        std::optional<id3v2> v2;
    }; // struct id3


} // namespace mpg123

#endif
