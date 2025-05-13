/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <cassert>

#include "mpg123xx/handle.hpp"


using std::expected;
using std::unexpected;


namespace mpg123 {


    handle::handle(const char* decoder)
    {
        create(decoder);
    }


    handle::handle(const std::string& decoder)
    {
        create(decoder);
    }


    handle::~handle()
        noexcept
    {
        destroy();
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
        if (is_valid())
            mpg123_delete(release());
    }


    void
    handle::add_flags(unsigned flags)
        noexcept
    {
        int e = mpg123_param(raw, MPG123_ADD_FLAGS, flags, 0.0);
        assert(e == MPG123_OK);
    }


    void
    handle::remove_flags(unsigned flags)
        noexcept
    {
        int e = mpg123_param(raw, MPG123_REMOVE_FLAGS, flags, 0.0);
        assert(e == MPG123_OK);
    }


    unsigned
    handle::get_flags()
        const noexcept
    {
        long lval = 0;
        int e = mpg123_getparam(raw, MPG123_FLAGS, &lval, nullptr);
        assert(e == MPG123_OK);
        return lval;
    }


    void
    handle::set_flags(unsigned flags)
        noexcept
    {
        int e = mpg123_param(raw, MPG123_FLAGS, flags, 0.0);
        assert(e == MPG123_OK);
    }


    void
    handle::set_icy_interval(int value)
        noexcept
    {
        int e = mpg123_param(raw, MPG123_ICY_INTERVAL, value, 0.0);
        assert(e == MPG123_OK);
    }


    void
    handle::set_verbose(bool v)
        noexcept
    {
        int e = mpg123_param(raw, MPG123_VERBOSE, v, 0.0);
        assert(e == MPG123_OK);
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
        int e = mpg123_getformat(raw, &rate, &channels, &encoding);
        if (e != MPG123_OK)
            return unexpected{error{this}};
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
        auto result = try_set_format(rate, channels, encoding);
        if (!result)
            throw result.error();
    }


    expected<void, error>
    handle::try_set_format(long rate,
                           unsigned channels,
                           unsigned encoding)
        noexcept
    {
        int e = mpg123_format(raw, rate, channels, encoding);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
    }


    void
    handle::open_feed()
    {
        auto result = try_open_feed();
        if (!result)
            throw result.error();
    }


    expected<void, error>
    handle::try_open_feed()
        noexcept
    {
        int e = mpg123_open_feed(raw);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
    }


    void
    handle::open(const path& filename)
    {
        auto result = try_open(filename);
        if (!result)
            throw result.error();
    }


    expected<void, error>
    handle::try_open(const path& filename)
        noexcept
    {
        int e = mpg123_open(raw, filename.c_str());
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
    }


    void
    handle::open(const path& filename,
                 mpg123_channelcount channels,
                 mpg123_enc_enum encoding)
    {
        auto result = try_open(filename, channels, encoding);
        if (!result)
            throw result.error();
    }


    std::expected<void, error>
    handle::try_open(const path& filename,
                     mpg123_channelcount channels,
                     mpg123_enc_enum encoding)
        noexcept
    {
        int e = mpg123_open_fixed(raw, filename.c_str(), channels, encoding);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
    }


    void
    handle::close()
    {
        auto result = try_close();
        if (!result)
            throw result.error();
    }


    expected<void, error>
    handle::try_close()
        noexcept
    {
        int e = mpg123_close(raw);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
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


    std::expected<std::size_t, error>
    handle::try_read(void* buf,
                     std::size_t size)
        noexcept
    {
        std::size_t result = 0;
        int e = mpg123_read(raw, buf, size, &result);
        if (e != MPG123_OK)
            return unexpected{error{this}};
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
        int e = mpg123_decode_frame(raw,
                                    &num,
                                    reinterpret_cast<unsigned char**>(&data),
                                    &size);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return frame{
            .num = num,
            .samples = std::span<const std::byte>(data, size)
        };
    }


    void
    handle::feed(const void* buf,
                 std::size_t size)
    {
        auto result = try_feed(buf, size);
        if (!result)
            throw result.error();
    }


    expected<void, error>
    handle::try_feed(const void* buf,
                     std::size_t size)
        noexcept
    {
        int e = mpg123_feed(raw,
                            static_cast<const unsigned char*>(buf),
                            size);
        if (e != MPG123_OK)
            return unexpected{error{this}};
        return {};
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
        auto result = try_get_id3();
        if (!result)
            throw result.error();
        return std::move(*result);
    }


    expected<id3, error>
    handle::try_get_id3()
        noexcept
    {
        mpg123_id3v1* v1 = nullptr;
        mpg123_id3v2* v2 = nullptr;
        int e = mpg123_id3(raw, &v1, &v2);
        if  (e != MPG123_OK)
            return unexpected{error{this}};
        id3 result{ v1, v2 };
        mpg123_meta_free(raw);
        return result;
    }

} // namespace mpg123
