
.. toctree::
  :hidden:

  compile
  reference


Tocc's CLI Users Manual
-----------------------

Introduction
============

Tocc have different UIs. The official UI that comes with it by default, is a CLI (Command Line Interface). Its binary calls *tocc*, which you can inboke as follows::

  $ tocc --help

The above command will print out the help of the CLI.

Installation
============
If you download a binary package, simply install that. If you have source package,  instructions about how to compile and install CLI is available in :doc:`compile`.

Quick Start
===========

*The path that goes through the rules is long and hard, the path that goes through the examples is short and easy.*

So, let's begin with some examples.

In order to manage your files with Tocc, you need to import them into Tocc. Tocc keeps your files in a directory, and let you search through them using tags, for example. I will explain it in more details, later.

Let's say we choose ``/home/tocc-managed/``. It can be any empty directory. First we should initialize this directory (It should be done only once)::

  $ tocc-initialize /home/tocc-managed/

* Tip: You can test Tocc features, and at the end, simply remove the ``/home/tocc-managed/`` directory. Tocc keep individual database file inside each Tocc-managed directory, and by removing that, all of the changes will be vanished cleanly.

Now let's import some files and assign some tags to them::

  $ tocc -b /home/tocc-managed/ -i /media/photography/DSC00001.JPG -a photo good-shot landscape 2014-06-18

What a long command! Let's analyize it step by step.

First option, ``-b`` (or ``--base-path`` if you prefer long but meaningful form), tells Tocc where it should keeps its data. **Tip:** To simplify your commands, you can change directory to ``/home/tocc-managed/``, and you don't have to pass ``-b`` option anymore. CLI will use the current directory as the base path by default.

``-i`` (``--import``) says: import this file. It's a photo in our example.

``-a`` (``--assign``) says: assign these four tags to the just imported file.

What's happened again? We told Tocc to copy this photo in its own directory, and assign four tags to it.

Let's import some other files (I omitted ``-b``)::

  $ tocc -i /home/aidin/Documents/CV.md -a document my-cv mark-down
  $ tocc -i /media/photography/DSC0002.JPG -i /media/photography/DSC0003.JPG -a photo abstract 2014-07-12

Now that we have some files inside our ``tocc-managed`` directory, we can search through them::

  $ tocc -q tag = photo -p

It means: query all files that tagged *photo* (``-q``, ``--query``), and print them out (``-p``, ``--print``). Output is::

  DSC0001
  DSC0002
  DSC0003

These are the *Title* of those photos. You can also give ``--print`` a format::

  $ tocc -q tag = photo and tag = "2014-07*" -p name: {title}, tags: {tags}
    name: DSC0002, tags: [photo abstract 2014-06-16]
    name: DSC0003, tags: [photo abstract 2014-06-16]

As you can see, those words between brackets replaced with metadata of the file. And other things remained the same. Note that we used wild card in the query.

``--print`` is one of the actions you can perform on founded files. Another action is ``--assign``, as you see above: It assigns tag to the founded files. Let's add *hdr* tag to one of the photos::

  $ tocc -q title = DSC0002 -a hdr

Note that I used *title* in the query. I told Tocc to give me files that their title matches *DSC0002*.

Now, what if we want to edit a file?::

  $ vim `tocc -q tag = "my-cv" -p {physical_path}`

`{physical_path}` will replace with the full path to the file stored in file system. I just passed this path to *vim*. As simple as that!


How Tocc Works?
---------------------------

Tocc keeps two kind of data: Your actual files, and their metadata (mainly, tags that are assigned to them).

Tocc keeps your files in a directory on the file system. We call this direcory *Tocc Managed File System*. Files rename to some meaningless names, kept under meaningless directory structure (meaningless for humans, I mean!). For example, if *Tocc Managed File System* is ``/home/tocc-managed/``, you will some files like ``/opt/tocc-managed/00/00/01/3`` or ``/opt/tocc-managed/00/0c/6a/e``. These are the files that you're imported in Tocc.

In order to search these files, we need the metadata. Tocc creates a database file in the root of *Tocc Managed File System*, and keep metada of files inside it: Title of each file, tags that assigned to it, etc.

Note that you can have more than one *Tocc Managed File System*. Each of them have their own database and separate set of files.


Where to go from here
=====================

* :doc:`compile`
* :doc:`reference`

