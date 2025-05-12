/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "utils.hpp"


namespace mpg123::utils {

    std::string
    concat(const std::string& a,
           const std::string& b,
           const std::string& separator)
    {
        if (a.empty())
            return b;
        if (b.empty())
            return a;
        return a + separator + b;
    }


    std::string
    to_string(const mpg123_string* s)
    {
        if (s && s->fill)
            return std::string(s->p, s->fill - 1);
        else
            return {};
    }


    std::string
    to_string(const mpg123_string& s)
    {
        if (s.fill)
            return std::string(s.p, s.fill - 1);
        else
            return {};
    }


} // mpg123::utils
