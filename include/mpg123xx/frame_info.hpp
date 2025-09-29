/*
 * mpg123xx - A C++ wrapper for libmpg123
 * Copyright 2025  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef MPG123XX_FRAME_INFO_HPP
#define MPG123XX_FRAME_INFO_HPP

#include <mpg123.h>

namespace mpg123 {

    struct frame_info {

        mpg123_version version;   ///< The MPEG version (1.0/2.0/2.5).
        unsigned       layer;     ///< The MPEG Audio Layer (MP1/MP2/MP3).
        unsigned       rate;      ///< The sampling rate in Hz.
        mpg123_mode    mode;      ///< The audio mode (Mono, Stereo, Joint-stero, Dual Channel).
        unsigned       mode_ext;  ///< The mode extension bit flag.
        unsigned       framesize; ///< The size of the frame (in bytes, including header).
        unsigned       flags;     ///< MPEG Audio flag bits, from mpg123_flags
        unsigned       emphasis;  ///< The emphasis type.
        unsigned       bitrate;   ///< Bitrate of the frame (kbps).
        unsigned       abr_rate;  ///< The target average bitrate.
        mpg123_vbr     vbr;       ///< The VBR mode.

    }; // struct frame_info

} // namespace mpg123

#endif
