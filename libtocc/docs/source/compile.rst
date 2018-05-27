
How to Compile And Use libtocc
==============================

Installing UnQlite
------------------
*libtocc* depends on `UnQlite <http://unqlite.org>`_. So, first you need to
compile and install it on your system.

To do so, first get UnQlite from its website. un-compress it, and compile it
using your *C* compiler, as a shared object. If you use *gcc*, invoke the
following command::

  $ gcc -fPIC -shared -o libunqlite.so unqlite.c

Then, install it on you system libraries. (i.e. copy it to ``/usr/lib/``.)

**Note:** In current release of UnQlite (1.6.6) there's a bug that cause
compilation fail when linking it to a ``C++`` application. You need to apply
`this patch <http://bugs.symisc.net/index.php?do=details&task_id=111>`_ (which
also mentioned in `their forum
<http://unqlite.org/forum/compiler-error-when-building-for-c-g-v4-2-1>`_)
first.


Compiling libtocc
-----------------

1. Bootstraiping
^^^^^^^^^^^^^^^^

First step is bootstraping configure scripts. (You only need to do this if
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

In the above example, builded libraries will be placed in ``/opt/libtocc/lib/``
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


Test Units
----------

*libtocc* comes with some Unit Tests. They're placed in ``libtocc/tests``
directory. This section explains how to build and run these Unit Tests.

1. Bootstraping
^^^^^^^^^^^^^^^
Just like the bootstraping step of *libtocc* itself, you need Gnu Auto Tools.
Then invoke::

  $ cd /path/to/libtocc/tests
  $ ./bootstrap


2. Configuring
^^^^^^^^^^^^^^
Previous step creates a ``configure`` script. To run it, you need to add
``libtocc/src/`` directory to the includes path. The following command should
do it::

  $ ./configure CPPFLAGS="-I../src/" CXXFLAGS="-I../src/"

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


Linking Your Software with *libtocc*
------------------------------------

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


