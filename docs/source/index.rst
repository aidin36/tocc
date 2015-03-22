.. tocc documentation master file, created by
   sphinx-quickstart on Wed Mar 19 15:49:13 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. highlight:: cpp
  :linenothreshold: 5

*tocc*, a Tool for Obsessive Compulsive Classifiers
===================================================

.. toctree::
  :hidden:

  manual/index
  contribution
  developers/index
  uis

Tocc is a tag-based file management system. It also includes a tag-based file
system called Toccfs. The goal of Tocc is to provide a better system for
classifying files, which is more flexible than classic file systems that are based on a
tree of files and directories.

.. image:: _static/gplv3.png
  :alt: Gnu General Public License, version 3

Tocc is free software. It publishes under the terms of Gnu General Public
License version 3.

Who Needs Tocc?
===============
Traditional file systems are very limited for classifying files.
All you have are some directories.
Imagine that you want to store your photos on your hard drive. How are you
going to categorize them? By the date they were taken? What if you want to
find photos taken on a specific location? Or photos of a specific person?
Or if you're a photographer, you may also want to search your photos by
the techniques you used.

You can use photo management applications. But what about your collection of
books or music?

Tocc is here to help you! Using Tocc, you tag your stored files.
In the previous example, you can add these tags to a photo: ``2014-01-07``,
``portrait``, ``maria``. And another one with: ``2014-01-07``, ``landscape``,
``abstract``. Then you can simply search your photos with these tags.

In this way, you have a graph of tags and files instead of a tree.
It's much more flexible.

Tocc is very powerful in searching files. You can create complex queries like
``photo and landscape and (b&w or abstract)``. You can use *wildcards* and
*regular expressions* in your queries.

Tocc doesn't force any classification practices. You are free to categorize your
files any way you want. For example, you can use prefixes for your tags,
like ``type:pdf`` or ``author:Richard Bach``. You can write your
tags all in lower case, like ``read-later``, or in camel case like
``FreeSoftware``. It's all your choice!

Tocc also has different UIs, so you can work with whichever you feel comfortable
with.

Features
========

These are the main features of Tocc.

 * It can manage any kind of file. It's not limited to specific types of file.
 * It stores files and their related database in a regular directory, so you
   can store them everywhere, from you local file system, to a network storage
   or back them up in a DVD.
 * It has a File System interface, that lets any application use Tocc without
   any changes. In other words, other applications don't have to support Tocc
   specifically. It's compatible with everyone, out of the box.
 * There can be different UIs that work with Tocc: Command line interfaces,
   plugins for different launchers or different file browsers, etc.

Download
========

You can get the latest releases from
`Tocc Releases on Github <https://www.github.com/aidin36/tocc/releases/>`_.

Releases are signed with Aidin's key. You can get the key from public
Keyservers. The ID of the Key is ``79B75433``. (e.g. run this command:
``gpg --recv-keys 79B75433``)

You can also get the latest under-development source from Github::

  git clone https://www.github.com/aidin36/tocc.git

Documentation
=============

 * :doc:`manual/index`
 * `libtocc (API) <libtocc/index.html>`_
 * :doc:`developers/index`

Contribution
============

Tocc is free software, and it relies on people's contributions.
We need help in different parts of the project.
See our :doc:`contribution` page for finding out how you can
help the project.
