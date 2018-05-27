#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tocc-fs], [1.0.1], [aidin@t-o-c-c.com], [File System Interface for Tocc], [https://tocc.aidinhut.com])
AC_CONFIG_SRCDIR([main.cpp])

# Initializing Automake.
# [foreign] added, so automake won't check for missing NEWS, README, etc.
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_OFF_T

# Checks for library functions.
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([memset])

# Checks for UnQlite
# Since it's a C header, we need to set lang to C
AC_LANG_PUSH(C)
AC_CHECK_HEADER([unqlite.h], [], [AC_MSG_ERROR([Could not find unqlite.h header. Please make sure you have this header in your include path. Refer to documents for more info.])])
AC_SEARCH_LIBS([unqlite_open], [unqlite], [], [AC_MSG_ERROR([Could not find unqlite library. Please make sure you have this library in your libs path. Refer to documentations for more info.])])

PKG_CHECK_MODULES([FUSE], [fuse >= 2.9.2])

# Checking for libtocc.
# Setting lang to C++, because followings all are C++.
AC_LANG_PUSH(C++)
# The fourth argument is: don't try to compile this header.
AC_CHECK_HEADER([libtocc/front_end/manager.h], [], [AC_MSG_ERROR([Could not find libtocc/front_end/manager.h header. Please make sure you have libtocc headers in your include path. Refer to documents for more info.])], [-])
# `libtocc_exists' function used to check for libtocc. See the documentation
# about how to check for libtocc with Autoconf.
AC_SEARCH_LIBS([libtocc_exists], [tocc], [], [AC_MSG_ERROR([Could not find libtocc library. Please make sure you have this library in your libs path. Refer to documentations for more info.])])

# Changing back the language to C
AC_LANG_POP

# Output files.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

