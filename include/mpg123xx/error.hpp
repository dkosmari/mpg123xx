/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_ERROR_HPP
#define MPG123XX_ERROR_HPP

#include <stdexcept>


namespace mpg123 {

    class handle;


    struct error : std::runtime_error {
        error(int code);
        error(const handle& h);
    };


} // namespace mpg123

#endif
