#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libtocc], [1.0.0], [aidin@t-o-c-c.com], [libtocc], [http://t-o-c-c.com])
AC_CONFIG_SRCDIR([libtocc/front_end/manager.h])
#AC_CONFIG_HEADERS([config.h])

# Initializing Libtool
LT_INIT

# Initializing Automake
# [foreign] added, so automake won't check for missing NEWS, README, etc.
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
#AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])

# Checks for library functions.
AC_CHECK_FUNCS([mkdir pow strerror sendfile])

# Checking for UnQlite
AC_CHECK_HEADER([unqlite.h], [], [AC_MSG_ERROR([Could not find unqlite.h header. Please make sure you have this header in your include path. Refer to documentation for more info.])])
AC_SEARCH_LIBS([unqlite_open], [unqlite], [], [AC_MSG_ERROR([Could not find unqlite library. Please make sure you have this library in your libs path. Refer to documentation for more info.])])

# Option and variable for pkgconfig directory.
AC_ARG_WITH(pkgconfigdir,
            [  --with-pkgconfigdir=DIR    Where to install pkgconfig file. @<:@DIR/pkgconfig@:>@],
            [pkgconfigdir=$withval],
            [pkgconfigdir='${libdir}/pkgconfig'])
AC_SUBST(pkgconfigdir)

# Output files.
AC_CONFIG_FILES([Makefile libtocc.pc])
AC_OUTPUT
