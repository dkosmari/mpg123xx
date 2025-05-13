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
#include <filesystem>
#include <span>
#include <string>

#include <mpg123.h>

#include "basic_wrapper.hpp"
#include "error.hpp"
#include "format.hpp"
#include "frame.hpp"
#include "id3.hpp"


namespace mpg123 {

    using std::filesystem::path;


    struct handle : basic_wrapper<mpg123_handle*> {

        using parent_type = basic_wrapper<mpg123_handle*>;


        // Inherit constructors.
        using parent_type::parent_type;


        /// Move assignment.
        handle&
        operator =(handle&& other)
            noexcept = default;


        handle(const char* decoder = nullptr);

        handle(const std::string& decoder);


        ~handle()
            noexcept;


        void
        create(const char* decoder);

        void
        create(const std::string& decoder);


        void
        destroy()
            noexcept override;


        void
        add_flags(unsigned flags)
            noexcept;

        void
        remove_flags(unsigned flags)
            noexcept;


        unsigned
        get_flags()
            const noexcept;


        void
        set_flags(unsigned flags)
            noexcept;


        void
        set_icy_interval(int value)
            noexcept;


        void
        set_verbose(bool v = true)
            noexcept;


        format
        get_format();

        std::expected<format, error>
        try_get_format()
            noexcept;


        void
        set_format(long rate,
                   unsigned channels,
                   unsigned encoding);

        std::expected<void, error>
        try_set_format(long rate,
                       unsigned channels,
                       unsigned encoding)
            noexcept;


        void
        open_feed();

        std::expected<void, error>
        try_open_feed()
            noexcept;


        void
        open(const path& filename);


        std::expected<void, error>
        try_open(const path& filename)
            noexcept;

        void
        open(const path& filename,
             mpg123_channelcount channels,
             mpg123_enc_enum encoding);

        std::expected<void, error>
        try_open(const path& filename,
                 mpg123_channelcount channels,
                 mpg123_enc_enum encoding)
            noexcept;


        void
        close();

        std::expected<void, error>
        try_close()
            noexcept;


        std::size_t
        read(void* buf,
             std::size_t size);

        template<typename T,
                 std::size_t E>
        std::size_t
        read(std::span<T, E> buf)
        {
            return read(buf.data(), buf.size_bytes());
        }


        std::expected<std::size_t, error>
        try_read(void* buf,
                 std::size_t size)
            noexcept;

        template<typename T,
                 std::size_t E>
        std::expected<std::size_t, error>
        try_read(std::span<T, E> buf)
            noexcept
        {
            return try_read(buf.data(), buf.size_bytes());
        }


        frame
        decode_frame();

        std::expected<frame, error>
        try_decode_frame()
            noexcept;


        void
        feed(const void* buf,
             std::size_t size);

        std::expected<void, error>
        try_feed(const void* buf,
                 std::size_t size)
            noexcept;


        unsigned
        meta_check()
            noexcept;

        id3
        get_id3();

        std::expected<id3, error>
        try_get_id3()
            noexcept;

    };

} // namespace mpg123

#endif
