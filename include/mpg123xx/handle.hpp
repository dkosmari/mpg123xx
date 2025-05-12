/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_HANDLE_HPP
#define MPG123XX_HANDLE_HPP

#include <cstddef>
#include <expected>
#include <string>

#include <mpg123.h>

#include "basic_wrapper.hpp"
#include "error.hpp"
#include "format.hpp"
#include "frame.hpp"
#include "id3.hpp"


namespace mpg123 {

    struct handle : basic_wrapper<mpg123_handle*> {

        using parent_t = basic_wrapper<mpg123_handle*>;


        // Inherit constructors.
        using parent_t::parent_t;


        /// Move assignment.
        handle&
        operator =(handle&& other)
            noexcept = default;


        handle();

        handle(const char* decoder);

        handle(const std::string& decoder);


        void
        create();


        void
        create(const char* decoder);

        void
        create(const std::string& decoder);



        void
        destroy()
            noexcept override;

        void
        add_flags(unsigned flags);

        unsigned
        get_flags()
            const;

        void
        set_flags(unsigned flags);


        void
        set_icy_interval(int value);


        void
        set_verbose(bool v = true);


        format
        get_format();

        std::expected<format, error>
        try_get_format()
            noexcept;

        void
        set_format(long rate,
                   unsigned channels,
                   unsigned encoding);


        void
        open_feed();


        std::size_t
        read(void* buf,
             std::size_t size);

        std::expected<std::size_t, error>
        try_read(void* buf,
                 std::size_t size)
            noexcept;

        frame
        decode_frame();

        std::expected<frame, error>
        try_decode_frame()
            noexcept;


        void
        feed(const void* buf,
             std::size_t size);


        unsigned
        meta_check()
            noexcept;

        id3
        get_id3();

    };

} // namespace mpg123

#endif
