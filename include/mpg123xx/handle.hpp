/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_HANDLE_HPP
#define MPG123XX_HANDLE_HPP

#include <chrono>
#include <cstddef>
#include <expected>
#include <filesystem>
#include <optional>
#include <span>
#include <string>

#include <mpg123.h>

#include "basic_wrapper.hpp"
#include "error.hpp"
#include "format.hpp"
#include "frame.hpp"
#include "frame_info.hpp"
#include "id3.hpp"
#include "samples.hpp"


namespace mpg123 {

    using std::filesystem::path;


    using dbl_seconds = std::chrono::duration<double>;


    struct handle : detail::basic_wrapper<mpg123_handle*> {

        using parent_type = detail::basic_wrapper<mpg123_handle*>;


        // Inherit constructors.
        using parent_type::parent_type;


        /// Move constructor.
        handle(handle&& other)
            noexcept = default;

        /// Move assignment.
        handle&
        operator =(handle&& other)
            noexcept = default;


        handle(const char* decoder = nullptr);

        handle(const std::string& decoder);


        // Named constructor: create handle and open file.
        [[nodiscard]]
        static
        handle
        from_file(const path& filename);

        // Named constructor: create handle and open file.
        [[nodiscard]]
        static
        handle
        from_file(const path& filename,
                  mpg123_channelcount channels,
                  mpg123_enc_enum encoding);


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
        set_decoder(const std::string& name);

        std::expected<void, error>
        try_set_decoder(const std::string& name)
            noexcept;


        [[nodiscard]]
        std::string
        get_decoder()
            const;


        void
        open_feed();

        [[nodiscard]]
        std::expected<void, error>
        try_open_feed()
            noexcept;


        void
        open(const path& filename);

        [[nodiscard]]
        std::expected<void, error>
        try_open(const path& filename)
            noexcept;

        void
        open(const path& filename,
             mpg123_channelcount channels,
             mpg123_enc_enum encoding);

        [[nodiscard]]
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


        void
        scan();

        [[nodiscard]]
        std::expected<void, error>
        try_scan()
            noexcept;


        [[nodiscard]]
        std::size_t
        read(void* buf,
             std::size_t size);

        template<typename T,
                 std::size_t E>
        [[nodiscard]]
        std::size_t
        read(std::span<T, E> buf)
        {
            return read(buf.data(), buf.size_bytes());
        }


        [[nodiscard]]
        std::expected<std::size_t, error>
        try_read(void* buf,
                 std::size_t size)
            noexcept;

        template<typename T,
                 std::size_t E>
        [[nodiscard]]
        std::expected<std::size_t, error>
        try_read(std::span<T, E> buf)
            noexcept
        {
            return try_read(buf.data(), buf.size_bytes());
        }


        samples
        decode_frame();

        [[nodiscard]]
        std::expected<samples, error>
        try_decode_frame()
            noexcept;


        frame
        get_current_frame()
            const;

        [[nodiscard]]
        std::expected<frame, error>
        try_get_current_frame()
            const noexcept;


        dbl_seconds
        get_current_frame_duration()
            const;

        [[nodiscard]]
        std::expected<dbl_seconds, error>
        try_get_current_frame_duration()
            const noexcept;


        unsigned
        get_current_frame_size_samples()
            const;

        [[nodiscard]]
        std::expected<unsigned, error>
        try_get_current_frame_size_samples()
            const noexcept;


        off_t
        get_size_frames()
            const;

        [[nodiscard]]
        std::expected<off_t, error>
        try_get_size_frames()
            const noexcept;


        off_t
        get_size_samples()
            const;

        [[nodiscard]]
        std::expected<off_t, error>
        try_get_size_samples()
            const noexcept;


        frame_info
        get_frame_info()
            const;

        std::expected<frame_info, error>
        try_get_frame_info()
            const noexcept;


        void
        feed(const void* buf,
             std::size_t size);

        template<typename T,
                 std::size_t E>
        void
        feed(std::span<const T, E> buf)
        {
            feed(buf.data(), buf.size_bytes());
        }


        [[nodiscard]]
        std::expected<void, error>
        try_feed(const void* buf,
                 std::size_t size)
            noexcept;

        template<typename T,
                 std::size_t E>
        [[nodiscard]]
        std::expected<void, error>
        try_feed(std::span<const T, E> buf)
            noexcept
        {
            return try_feed(buf.data(), buf.size_bytes());
        }


        unsigned
        meta_check()
            const noexcept;

        id3
        get_id3()
            const;

        [[nodiscard]]
        std::expected<id3, error>
        try_get_id3()
            const noexcept;

    };

} // namespace mpg123

#endif
