#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mpg123xx],
        [0.0],
        [https://github.com/dkosmari/mpg123xx/issues],
        [],
        [https://github.com/dkosmari/mpg123xx])
AC_CONFIG_SRCDIR([src/mpg123.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CXX
AX_APPEND_COMPILE_FLAGS([-std=c++23], [CXX])
AC_LANG([C++])

AC_PROG_RANLIB


PKG_CHECK_MODULES([MPG123], [libmpg123])


AC_ARG_ENABLE([examples],
              [AS_HELP_STRING([--enable-examples], [enable building examples])],
              [],
              [enable_examples=no])
AM_CONDITIONAL([ENABLE_EXAMPLES], [test x$enable_examples = xyes])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT


AC_MSG_NOTICE([Build examples: $enable_examples])
