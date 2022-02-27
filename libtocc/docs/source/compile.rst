How to Compile And Use libtocc
==============================

Installing UnQlite
------------------
*libtocc* depends on `UnQlite <http://unqlite.org>`_. So, first you need to
compile and install it on your system.

You need to pay for recent versions of Unqlite. However, older versions were
free. You can obtain the free version from the `Tocc's Releases <https://github.com/aidin36/tocc/releases>`_.

Un-compress the package, then run::

  $ ./configure
  $ make
  $ make install

Compiling libtocc for Unix-like OS's (Linux, BSD, etc)
------------------------------------------------------

1. Bootstrapping
^^^^^^^^^^^^^^^^

First step is bootstrapping configure scripts. (You only need to do this if
you get the latest source from the repository. If you have one of the released
source packages, this step is already done for you.)

You need Gnu Auto Tools installed: *libtool*, *autoconf* and *automake*. Then,
simply invoke::

  $ cd /path/to/libtocc/src/
  $ ./bootsrap

It creates *configure* script.

2. Configuring
^^^^^^^^^^^^^^

Now, you need to configure build scripts. Normally, you only need to invoke::

  $ ./configure

It should be enough for most cases. Here some other common things you may want
to do.

**Installing Somewhere Else**: By default, *libtocc* will be installed on the
global *lib* and *include* directories of your system. (Usually
``/usr/local/lib/`` and ``/usr/local/include``.) But if you
want to install it somewhere else, you can pass ``--prefix`` option to the
``configure`` script::

  $ ./configure --prefix=/opt/libtocc/

In the above example, built libraries will be placed in ``/opt/libtocc/lib/``
and public headers in ``/opt/libtocc/include``.

**Optimized/Debug Build**: By default, *libtocc* mades with ``-g`` and ``-O2``.
If you want to overwrite these options, you can pass ``CXXFLAGS`` to
``configure`` script. For example, to build non-optimized for debuging::

  $ ./configure CXXFLAGS="-g -O0"

Or optimized without debug symbols::

  $ ./configure CXXFLAGS="-O2"

3. Building
^^^^^^^^^^^

Now that everything configured, simply invoke::

  $ make

You can pass ``CXXFLAGS`` in this step, too. But it's not recommended.

4. Installing
^^^^^^^^^^^^^

By invoking::

  $ make install

builded library and its public headers will be copied to the specified
prefix. For example, if prefix is ``/usr/local/``, libraries will be copied
to ``/usr/local/lib/`` and headers to ``/usr/local/include``.


Compiling libtocc for Windows with Microsoft Visual C++
-------------------------------------------------------

Note: libtocc does not compile correctly with MSVC 2019 but it does with
MSVC 2017 or MSVC 2021.

1. Open solution file ``tocc\msvc\libtocctests.sln`` in MSVC.

2. Select project ``libtocc`` and do a build.

3. The library file will be produced in ``tocc\msvc\x64\release\libtocc.lib`` or ``tocc\msvc\x64\debug\libtocc.lib``





Test Units
----------

*libtocc* comes with some Unit Tests. They're placed in ``libtocc/tests``
directory. This section explains how to build and run these Unit Tests.

Installing Catch2 for Unix-like OS's (Linux, BSD, etc)
------------------------------------------------------

1. Download Catch2 <https://github.com/catchorg/Catch2> to a temporary directory. Make sure you have the ``devel`` branch.
2. cd to the ``extras`` suddirectory of the temporary directory.
3. Invoke:

  $ gcc cache_amalgamated.cpp -o cache_amalgamated.o

  $ ar rcs libcache_amalgamated.a cache_amalgamatd.o

  $ sudo cp libcache_amalgamated.a /usr/local/lib

  $ sudo cp cache_amalgamated.hpp /usr/local/include


Building and running test units for Unix-like OS's (Linux, BSD, etc.)
---------------------------------------------------------------------

1. Bootstrapping
^^^^^^^^^^^^^^^^
Just like the bootstrapping step of *libtocc* itself, you need Gnu Auto Tools.
Then invoke::

  '
  $ cd /path/to/libtocc/tests
  $ ./bootstrap
  
'

2. Configuring
^^^^^^^^^^^^^^
Previous step creates a ``configure`` script. To run it, you need to add
``libtocc/src/`` directory to the includes path. The following command should
do it::

  $ ./configure CPPFLAGS="-I../src/ -I../tests" LDFLAGS="-L/usr/local/lib" CXXFLAGS="-I../src/ -I../tests" LIBS="-lcatch_amalgamated" 
  
You can do this by typing:

  $ ./config

Also, if you installed *libtocc* library in a non-standard path (where ``ld``
can't find it by default, say ``/opt/libtocc/lib/``) you need to add that to
the libraries search path::

  $ ./configure CPPFLAGS="-I../src/" CXXFLAGS="-I../src/" LDFLAGS="-L/opt/libtocc/lib"

Like it mentioned in *libtocc*, you can also overwrite optimization flags here.
Though the default is OK.

3. Building
^^^^^^^^^^^
If previous step was OK, you can run::

  $ make

in order to build unit tests.

**Note:** You don't need to install unit tests. You can run it from the same
directory.

4. Running
^^^^^^^^^^
Invoke unit tests using::

  $ ./libtocctests

Again, if you installed *libtocc* somewhere that ``ld`` can't find it by
default, you need to specify that path::

  $ LD_LIBRARY_PATH=/opt/libtocc/lib/ ./libtocctests

5. How to Report a Problem
^^^^^^^^^^^^^^^^^^^^^^^^^^
If unit tests failed on you machine, do us a favor and report it. To do so,
run *libtocctests* like this::

  $ ./libtocctests 2>&1 > tests.log

Then send ``tests.log`` file to *tocc@aidinhut.com*, and provide your platform
information, such as your OS and its version.


Installing Catch2 for Windows
------------------------------------------------------

1. Download Catch2 <https://github.com/catchorg/Catch2> to a temporary directory. Make sure you have the ``devel`` branch.
2. cd to the ``extras`` suddirectory of the temporary directory.
3. Copy ``libcache_amalgamated.cpp`` and ``cache_amalgamated.hpp`` to ``tocc/libtocc/tests`` 



Building and running test units for Windows with Microsoft Visual C++
---------------------------------------------------------------------

1. Open solution file ``tocc\msvc\libtocctests.sln`` in MSVC.
2. Select project ``libtocctests``.
3. Build this project.
4. The program will be in ``tocc\msvc\x64\release\libtocctests.exe`` or ``tocc\msvc\x64\debug\libtocctests.exe``. Execute the program from a command prompt.



Linking Your Software with *libtocc* for Unix-like OS's (Linux, BSD, etc)
-------------------------------------------------------------------------

Using Autotools
^^^^^^^^^^^^^^^

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
