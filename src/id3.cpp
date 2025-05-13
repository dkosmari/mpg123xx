/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "mpg123xx/id3.hpp"

#include "utils.hpp"


using mpg123::utils::to_string;


namespace mpg123 {

    namespace {

        template<std::size_t N>
        bool
        contains(const char (&haystack)[N],
                 char needle)
            noexcept
        {
            for (char c : haystack)
                if (c == needle)
                    return true;
            return false;
        }


        template<std::size_t N>
        std::string
        array_to_str(const char (&src)[N])
        {
            if (contains(src, '\0'))
                return src;
            else
                return std::string(src, src + N);
        }

    } // namespace


    id3v1::id3v1(const mpg123_id3v1* src) :
        title{array_to_str(src->title)},
        artist{array_to_str(src->artist)},
        album{array_to_str(src->album)},
        year{array_to_str(src->year)},
        comment{array_to_str(src->comment)},
        genre{src->genre}
    {
        // Handle ID3v1.1
        if (src->comment[28] == '\0')
            track = src->comment[29];
    }


    text::text(const mpg123_text* src)
    {
        if (src) {
            lang = array_to_str(src->lang);
            id = array_to_str(src->id);
            description = to_string(src->description);
            data = to_string(src->text);
        }
    }


    text::text(const mpg123_text& src) :
        lang{array_to_str(src.lang)},
        id{array_to_str(src.id)},
        description{to_string(src.description)},
        data{to_string(src.text)}
    {}


    id3v2::id3v2(const mpg123_id3v2* src) :
        version{src->version},
        title{to_string(src->title)},
        artist{to_string(src->title)},
        album{to_string(src->album)},
        year{to_string(src->year)},
        genre{to_string(src->genre)},
        comment{to_string(src->comment)}
    {
        for (std::size_t i = 0; i < src->comments; ++i)
            comments.push_back(src->comment_list[i]);

        for (std::size_t i = 0; i < src->texts; ++i)
            texts.push_back(src->text[i]);

        for (std::size_t i = 0; i < src->extras; ++i)
            extras.push_back(src->extra[i]);

        // TODO: process pictures

    }


    id3::id3(mpg123_id3v1* tag1,
             mpg123_id3v2* tag2)
    {
        if (tag1)
            v1.emplace(tag1);
        if (tag2)
            v2.emplace(tag2);
    }



} // namespace mpg123
