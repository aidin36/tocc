
How to Compile And Use libtocc
==============================

Compile
-------

Use with Autotools
------------------
If you use Gnu Autotools for your application, you can check for and link
against *libtocc* in one of these ways.

Building *libtocc* with ``make`` produces and installs ``libtocc.pc`` file.
This file used by ``pkg-config`` tool. So, you can use macros like
``PKG_CHECK_MODULES`` in your ``autoconf`` (``configure.ac``) file.

An alternative way, if you don't want to use ``pkg-config``, is to use the
good old ``AC_SEARCH_LIBS``. For making life easier, *libtocc* have a function
in itself called ``libtocc_exists``, which is a ``C`` function. So, you can
simply use it like this::

  AC_SEARCH_LIBS([libtocc_exists], [tocc])


