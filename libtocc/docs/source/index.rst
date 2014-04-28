.. libtocc documentation master file, created by
   sphinx-quickstart on Mon Mar 10 05:40:33 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. highlight:: cpp
  :linenothreshold: 5

Documentation of the *libtocc*
================================

.. toctree::
  :hidden:

  overview
  compile
  api_reference


Introduction
============

*libtocc* is the engine of the Tocc project. All of the functionalities
are implemented in this library. Other components are just UIs for *libtocc*.
So, there can be different UIs that work in parallel.

*libtocc* have a very simple, clean and complete API. It is written in
``C++`` but there can be wrappers for other languages.

This document explains how to use this library.


Quick Start
===========
Compiling from Source
---------------------
*libtocc* depends on `UnQlite <http://unqlite.org>`_. So, first get UnQlite
and compile it on your system. Then, install it on your system libraries.
(e.g. copy it to ``/usr/lib/``.)

**Note:** In current release of UnQlite (1.6.6) there's a bug that cause
compilation fail when using in a ``C++`` application. You need to apply
`this patch <http://bugs.symisc.net/index.php?do=details&task_id=111>`_ (which
also mentioned in `their forum
<http://unqlite.org/forum/compiler-error-when-building-for-c-g-v4-2-1>`_)
first.

Preparing
^^^^^^^^^
If you get one of the relased source packages, this step is already done. So
you can skip this section. But if you have the latest code from Github,
read on.

You need Gnu Autotools (Libtool, Autoconf and Automake).
Go to ``libtocc/src/`` directory, and run ``bootstrap``
script in there. It will create ``configure`` script.

Making Source
^^^^^^^^^^^^^

Go to ``libtocc/src`` directory, then run::

  ./configure
  make
  make install

Note that latest command needs super user privilage.

This will install the compiled library in ``/usr/local/lib`` and
header files in ``/usr/local/include`` by default.
If you want to install it on another directory, pass ``--prefix`` option
to ``configure`` script. i.e.::

  ./configure --prefix=./bin/

Which installs compiled library in ``./bin/lib/`` and headers in
``./bin/include/``.

A Minimal Example
-----------------
The following is a minimal example of an application that uses *libtocc*::

  #include <iostream>
  #include "libtocc.h"

  int main(int argc, char* argv[])
  {
    // The argument is the path to where tocc-managed files should be
    // kept. Replace it with an existing path.
    libtocc::Manager manager("/opt/tocc-managed/");

    // Copying a file from the file system to the tocc-managed file system.
    // The second argument is the title of this file.
    libtocc::FileInfo new_file_info =
      manager.copy_file("/home/aidin/photos/portrate01.jpeg",
                        "A Beautiful Portrate");

   // Printing out information of the copied file.
   std::cout << new_file_info << std::endl;
  } 

Put it in ``sample.cpp`` file, and then simply compile it::

  $g++ -o sample sample.cpp -ltocc -lunqlite

**Note:** At the current version, you also have to link your application
against the ``libunqlite.so``. This will be fix in future versions.

Here's an explanation of what happened. First, you need to include
``libtocc.h`` which defines the interface of the *libtocc*. The main class in
that file is the :cpp:class:`libtocc::Manager` class. All of the Tocc functionalities
are accessible through Manager class. In its constructor, it gets a path to a
directory that it should keeps its files and database. After that, we invoked
the :cpp:func:`libtocc::Manager::copy_file` method in order to copy a file from
the traditional file system to the tocc-managed file system. It's a photo, and
its title is "A Beautiful Portrate".


Where to go from here
=====================

* :doc:`overview`
* :doc:`compile`
* :doc:`api_reference`

