/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_UTILS_HPP
#define MPG123XX_UTILS_HPP

#include <string>

#include <mpg123.h>


namespace mpg123::utils {

    std::string
    concat(const std::string& a,
           const std::string& b,
           const std::string& separator = ",");


    std::string
    to_string(const mpg123_string* s);

    std::string
    to_string(const mpg123_string& s);

} // mpg123::utils

#endif
