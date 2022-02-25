

.. toctree::
  :hidden:


How to Compile Tocc's Official CLI in a Unix-like OS (Linux, BSD, etc)
======================================================================

In order to compile CLI, you need first have ``libtocc`` compiled and
installed. Follow the instructions in
`How to Compile And Use libtocc </libtocc/compile.html>`_ page.

Source of the CLI is available in ``cli/src/`` directory. Change your
current directory to it, and follow the instructions.

Bootstrapping
-------------

First step is to create a ``configure`` script. If you downloaded a released
source package, this step already done. You can skip it.

You need *Gnu Auto Tools*, e.g. *Libtool*, *Autoconf* and *Automake* installed.
Then, simply invoke ``bootstrap`` script::

  ./bootstrap

Configuring
-----------

Previous step created a ``configure`` script. Normally, you don't need to pass
any options::

  ./configure

By default, CLI binary (``tocc``) will be installed in the default ``bin``
directory. Usually ``/usr/local/bin/``. If you want to install it into another
directory, you can pass ``--prefix`` option to ``configure`` script::

  ./configure --prefix=/opt/tocc/

Which installs binary in ``/opt/tocc/bin/``.

Making
------

Now that you configured CLI, you can invoke ``make`` in order to compile the
source::

  make

Installing
----------

If previous step goes without any error, simply invoke::

  make install

(Usually, you need super user access to invoke this command.)

This will install ``tocc`` binary in the directory you specified using
``--prefix`` (or the default directory).



How to Compile Tocc's Official CLI in Windows using Microsoft Visual C++
========================================================================

1. Open solution file ``tocc\msvc\libtocctests.sln`` in MSVC.
2. Select project ``tocc``.
3. Build this project.
4. Select project ``tocc-initialize``.
5. Build this project.
6. The programs will be ``tocc.exe`` and ``tocc-initialize`` in directory ``tocc\msvc\x64\release`` or ``tocc\msvc\x64\debug``.

