/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "mpg123xx/handle.hpp"

// TODO: get rid of these macros.

#define CHECK(e)                                \
    do {                                        \
        if (e != MPG123_OK)                     \
            throw error{*this};                 \
    } while (false)


#define ECHECK(e)                                       \
    do {                                                \
        if (e != MPG123_OK)                             \
            return std::unexpected{error{*this}};       \
    } while (false)


using std::expected;
using std::unexpected;


namespace mpg123 {

    handle::handle()
    {
        create();
    }


    handle::handle(const char* decoder)
    {
        create(decoder);
    }


    handle::handle(const std::string& decoder)
    {
        create(decoder);
    }


    void
    handle::create()
    {
        create(nullptr);
    }


    void
    handle::create(const char* decoder)
    {
        int e = 0;
        auto new_raw = mpg123_new(decoder, &e);
        if (!new_raw)
            throw error{e};
        destroy();
        acquire(new_raw);
    }


    void
    handle::create(const std::string& decoder)
    {
        create(decoder.data());
    }


    void
    handle::destroy()
        noexcept
    {
        if (raw)
            mpg123_delete(release());
    }


    void
    handle::add_flags(unsigned flags)
    {
        auto e = mpg123_param(raw, MPG123_ADD_FLAGS, flags, 0.0);
        CHECK(e);
    }


    unsigned
    handle::get_flags()
        const
    {
        long lval = 0;
        double dval = 0;
        auto e = mpg123_getparam(const_cast<mpg123_handle*>(raw),
                                 MPG123_FLAGS, &lval, &dval);
        CHECK(e);
        return lval;
    }


    void
    handle::set_flags(unsigned flags)
    {
        auto e = mpg123_param(raw, MPG123_FLAGS, flags, 0.0);
        CHECK(e);
    }


    void
    handle::set_icy_interval(int value)
    {
        auto e = mpg123_param(raw, MPG123_ICY_INTERVAL, value, 0.0);
        CHECK(e);
    }


    void
    handle::set_verbose(bool v)
    {
        auto e = mpg123_param(raw, MPG123_VERBOSE, v, 0.0);
        CHECK(e);
    }


    format
    handle::get_format()
    {
        auto result = try_get_format();
        if (!result)
            throw result.error();
        return *result;
    }


    std::expected<format, error>
    handle::try_get_format()
        noexcept
    {
        long rate = 0;
        int channels = 0;
        int encoding = 0;
        auto e = mpg123_getformat(raw, &rate, &channels, &encoding);
        ECHECK(e);
        return format{
            .rate = rate,
            .channels = static_cast<unsigned>(channels),
            .encoding = static_cast<unsigned>(encoding)
        };
    }


    void
    handle::set_format(long rate,
                       unsigned channels,
                       unsigned encoding)
    {
        auto e = mpg123_format(raw, rate, channels, encoding);
        CHECK(e);
    }


    void
    handle::open_feed()
    {
        auto e = mpg123_open_feed(raw);
        CHECK(e);
    }


    std::size_t
    handle::read(void* buf,
                 std::size_t size)
    {
        auto result = try_read(buf, size);
        if (!result)
            throw result.error();
        return *result;
    }


    std::expected<std::size_t,
                  error>
    handle::try_read(void* buf, std::size_t size)
        noexcept
    {
        std::size_t result = 0;
        auto e = mpg123_read(raw, buf, size, &result);
        ECHECK(e);
        return result;
    }


    frame
    handle::decode_frame()
    {
        auto result = try_decode_frame();
        if (!result)
            throw result.error();
        return *result;
    }


    std::expected<frame, error>
    handle::try_decode_frame()
        noexcept
    {
        off_t num = 0;
        std::byte* data = nullptr;
        std::size_t size = 0;
        auto e = mpg123_decode_frame(raw,
                                     &num,
                                     reinterpret_cast<unsigned char**>(&data),
                                     &size);
        ECHECK(e);
        return frame{
            .num = num,
            .samples = std::span<const std::byte>(data, size)
        };
    }


    void
    handle::feed(const void* buf,
                 std::size_t size)
    {
        auto e = mpg123_feed(raw,
                             static_cast<const unsigned char*>(buf),
                             size);
        CHECK(e);
    }


    unsigned
    handle::meta_check()
        noexcept
    {
        return mpg123_meta_check(raw);
    }


    id3
    handle::get_id3()
    {
        mpg123_id3v1* v1 = nullptr;
        mpg123_id3v2* v2 = nullptr;
        auto e = mpg123_id3(raw, &v1, &v2);
        CHECK(e);
        return { .v1 = v1, .v2 = v2 };
    }

} // namespace mpg123
