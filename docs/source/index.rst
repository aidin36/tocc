.. tocc documentation master file, created by
   sphinx-quickstart on Wed Mar 19 15:49:13 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. highlight:: cpp
  :linenothreshold: 5

*tocc*, a Tool for Obsessive Compulsive Classifers
==================================================

.. toctree::
  :hidden:

  manual/index
  contribution


Tocc is a tag-based file management system. It also includes a tag-based file
system called Toccfs. The goal of Tocc is to provide a better system for
classifying files, more flexible than classic file systems that are based on a
tree of files and directories.

.. image:: _static/gplv3.png
  :alt: Gnu General Public License, version 3
Tocc is free software. It publishes under the terms of Gnu General Public
License version 3.

Who Needs Tocc?
===============
Traditional file systems are very limit for classifiying files.
All you have is some directories.
Imagine that you want to store your photos on your hard drive. How you're
going to categorize them? By the date they taken? Then what if you want to
find photos taken on a specific location? Or photos of a specific person?
Or if you're a photographer, you may also want to search your photos by
the techniques you used.

You can use photo management applications. But what about your collection of
books or music?

Tocc is here to help you! Using Tocc, you tag your stored files.
In the previous example, you can add these tags to a photo: ``2014-01-07``,
``portrate``, ``maria``. And another one with: ``2014-01-07``, ``landscape``,
``abstract``. Then you can simply search your photos with these tags.

In this way, you have a graph of tags and files instead of a tree.
It's much more flexible.

Tocc is very powerfull in searching files. You can create complex queries like
``photo and landscape and (b&w or abstract)``. You can use *wildcard* and
*Regular Expression* in your queries.

Tocc don't force any classification practice. You are free to categorize your
files anyhow you want. For example, you can use prefixes for your tags,
like ``type:pdf`` or ``author:Richard Bach``. You can write your
tags all in lower case, like ``read-later``, or in camel case like
``FreeSoftware``. It's all your choice!

Tocc also have different UIs, so you can work with whichever you feel comfortable
with.

Features
========

Download
========

You can get the latest releases from
`Tocc Releases on Github <https://www.github.com/aidin36/tocc/releases/>`_.

You can also get the latest under-develop source from Github::

  git clone https://www.github.com/aidin36/tocc.git

Documentation
=============

 * :doc:`manual/index`
 * `libtocc (API) <libtocc/index.html>`_
 * :doc:`developers/index`

Contribution
============

Tocc is a free software, and it relys on people contribution.
We need help in different parts of the project.
See our :doc:`contribution` page for finding out how you can
help the project.

About
=====


