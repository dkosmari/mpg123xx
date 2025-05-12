/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <ostream>
#include <sstream>

#include "mpg123xx/format.hpp"

#include "utils.hpp"


using mpg123::utils::concat;


namespace mpg123 {

    namespace {

        std::string
        channels_to_string(unsigned c)
        {
            std::string result;
            if (c & MPG123_MONO)
                result = concat(result, "mono");
            if (c & MPG123_STEREO)
                result = concat(result, "stereo");
            if (c > 3)
                result = concat(result, "unknown");
            return result;
        }


        std::string
        encoding_to_string(unsigned enc)
        {
            switch (enc) {
                case MPG123_ENC_SIGNED_16:   return "signed-16-bit";
                case MPG123_ENC_UNSIGNED_16: return "unsigned-16-bit";
                case MPG123_ENC_UNSIGNED_8:  return "unsigned-8-bit";
                case MPG123_ENC_SIGNED_8:    return "signed-8-bit";
                case MPG123_ENC_ULAW_8:      return "ulaw-8-bit";
                case MPG123_ENC_ALAW_8:      return "alaw-8-bit";
                case MPG123_ENC_SIGNED_32:   return "signed-32-bit";
                case MPG123_ENC_UNSIGNED_32: return "unsigned-32-bit";
                case MPG123_ENC_SIGNED_24:   return "signed-24-bit";
                case MPG123_ENC_UNSIGNED_24: return "unsigned-24-bit";
                case MPG123_ENC_FLOAT_32:    return "float-32-bit";
                case MPG123_ENC_FLOAT_64:    return "float-64-bit";
                default:                     return std::to_string(enc);
            }
        }

    } // namespace
    std::string
    to_string(const format& fmt)
    {
        std::ostringstream out;
        out << "{ rate: " << std::to_string(fmt.rate) << " Hz ; "
            << "channels: " << channels_to_string(fmt.channels) << " ; "
            << "encoding: " << encoding_to_string(fmt.encoding) << " }";
        return out.str();
    }


    std::ostream&
    operator <<(std::ostream& out,
                const format& fmt)
    {
        return out << to_string(fmt);
    }

} // namespace mpg123
