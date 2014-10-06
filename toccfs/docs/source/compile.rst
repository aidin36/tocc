
.. toctree::
  :hidden:


Compiling Toccfs from Source
----------------------------

Requirements
============
*toccfs* wrote using FUSE (File System in User Environment) library. So, you
need to have FUSE installed on your system. Usually, you can find a package
like *libfuse-dev* among your distro's packages. If not, try get it from its
web site: `fuse.sourceforge.net <http://fuse.sourceforge.net>`_.

You also need *libtocc* compiled and installed on you system. If you didn't
do this already, see `How to Compile And Use libtocc </libtocc/compile.html>`_.

Bootstraping
============
First step is to create a ``configure`` script. If you downloaded a released
source package, this step already done. You can skip it.

You need *Gnu Auto Tools*, e.g. *Libtool*, *Autoconf* and *Automake* installed.
Then, simply invoke ``bootstrap`` script::

  ./bootstrap

Configuring
===========
Previous step created a ``configure`` script. Normally, you don't need to pass
any options::

  ./configure

By default, *toccfs* binary (``toccfs``) will be installed in the default ``bin``
directory. Usually ``/usr/local/bin/``. If you want to install it into another
directory, you can pass ``--prefix`` option to ``configure`` script::

  ./configure --prefix=/opt/tocc/

Which installs binary in ``/opt/tocc/bin/``.

Making
======

Now that you configured CLI, you can invoke ``make`` in order to compile the
source::

  make

Installing
==========

If previous step goes without any error, simply invoke::

  make install

(Usually, you need super user access to invoke this command.)

This will install ``toccfs`` binary in the directory you specified using
``--prefix`` (or the default directory).


