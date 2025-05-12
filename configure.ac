#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mpg123xx], [0.0], [])
AC_CONFIG_SRCDIR([src/mpg123.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CXX
AX_APPEND_COMPILE_FLAGS([-std=c++23], [CXX])
AC_LANG([C++])

AC_PROG_RANLIB


PKG_CHECK_MODULES([MPG123], [libmpg123])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
