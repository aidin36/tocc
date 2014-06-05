
.. toctree::
  :hidden:

  compile
  reference


Documentation of the Tocc's Official CLI
========================================


Introduction
============

Tocc comes with an official command line interface (CLI). After you install it,
a ``tocc`` command will be add to your shell.

Installation
============

If you have Tocc's source package, instructions about how to compile and
install it is available in :doc:`compile`.

Quick Start
===========

First, you need to choose a path that Tocc keep its files in there. Let's
assume we choose ``/opt/tocc-managed/``.

* Note: You can test Tocc features, and at the end, simply remove the
  ``/opt/tocc-managed/`` directory. Tocc keep individual database file
  inside each Tocc-managed directory, and by removing that, all of the
  changes will be vanished cleanly.

Make sure the path you choosed is exist.
First step is to import some files in this directory::

  tocc --base-path /opt/tocc-managed/ --import /media/photos/2014/05/IMG0015.jpg --assign photo landscape

Let's see what happened. First, we told Tocc that where it should keeps its
files, using :option:`--base-path option <-b>`. Then, we told it to
:option:`import <-i>` an image file called ``IMG0015.jpg``, and at the same
time :option:`assign <-a>` two tags to it: ``photo`` and ``landscape``. Note
that tags are separated using space character.

In order to make life easier, you can change you directory to the tocc-managed
directory, and omits the ``--base-path`` option::

  cd /opt/tocc-managed/
  tocc --import  /media/photos/2014/05/IMG0017.jpg --asign photo "my love"

Note that we assigned a two-word tag: *my love*. We put it inside two quote
characters, so Tocc know that it's a single tag, not two tags separated by
space.

Now that we have some files in tocc-managed directory, we can query them::

  tocc --query tag = photo --print

  IMG0015
  IMG0017

* Note that you must put spaces before and after ``=`` operator.

Using :option:`--query <-q>` option, we can query files using their meta data
(i.e. their tags, creation date, etc.). In the previous example, we told Tocc
to *find all the files that have a `photo' tag*.

:option:`--print <-p>` tells Tocc to print the result. Tocc can do different
action on files founded by query. *--print* simply print out title of files.
:option:`--assign <-a>` is another example of actions, as you see before.

Queries can have more terms, separated by ``and`` or ``or``::

  tocc --query tag = photo and tag = "my love" --print

  IMG0017

  tocc --query tag = "my love" or tag = landscape --print

  IMG0015
  IMG0017

You can also edit the files founded by a query::

  tocc --query tag = landscape --assign hdr

Which assigns *hdr* tag to all the files that have *landscape* tag.


Where to go from here
=====================

* :doc:`compile`
* :doc:`reference`

