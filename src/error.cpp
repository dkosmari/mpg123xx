/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <mpg123.h>

#include "mpg123xx/error.hpp"

#include "mpg123xx/handle.hpp"


namespace mpg123 {

    error::error(int code) :
        std::runtime_error{mpg123_plain_strerror(code)}
    {}


    error::error(const handle* h) :
        std::runtime_error{mpg123_strerror(const_cast<mpg123_handle*>(h->data()))}
    {}

} // namespace mpg123
