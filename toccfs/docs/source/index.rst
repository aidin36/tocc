
.. toctree::
  :hidden:

  compile


Tocc File System (toccfs)
=========================

Tocc stores all the files in a special structure, and lets other applications query and use the files using its API. This means that if any application wants to use files stored using Tocc, it should know how to talk with Tocc. It's not possible in all cases. (At least, not until Tocc become famous enough that everyone supports it ;-) )

To let other applications use files stored with Tocc, there's a special file system available: *toccfs*

*toccfs* looks like any regular file system: you mount it somewhere, and then you can see your files as if they were stored in a traditional file system: in a tree of direcories and files.

I this way, any other applications that can only understand the traditional way of storing files can use Tocc without any change. You can browse your files using *Nautilus*, access them over a network using *Samba*, and things like that.

Installation
------------
If you download a binary package of *toccfs*, installing that would be enough. If you have the source code package, see :doc:`compile`.

How to Use
----------

First, mount your *Tocc Managed File System* somewhere::

  $ toccfs /home/tocc-managed/ /mnt/traditional-access/

The first argument is the path to *Tocc Managed File System* (where Tocc stores its files, i.e. the *base path* you pass to CLI when working with it.) The second argument is the mount point.

Now, you can access your files from ``/mnt/traditional-access/`` using any tool you want. For example::

  $ ls /mnt/traditional-access/
     photo  good-shot   landscape  abstract  document  my-cv

  $ ls /mnt/traditional-access/photo/
     abstract  landscape  good-shot  DSC0001  DSC0002  DSC0003

But wait a minute! What happened?

In order to map a structure of *Files and Tags* to *Directories and Files*, *toccfs* shows each tag as a directory, and each file that has that tag as a file inside that directory.

Let's explain it with an example.

If you list files inside ``/mnt/traditional-access/photo/abstract/``, it means you asked Tocc to give you all the files that are tagged *photo* and *abstract*. Or if you access ``/mnt/traditional-access/photo/DSC00001``, it means you asked Tocc to give you a file tagged *photo* and its title is *DSC0001*.

In other word, each path is a query to Tocc.

Now that you know how it works, let me tell you the rules of the query language. When you pass a path to *toccfs*, it compiles it as follows:

1. If it corresponds exactly to a *Traditional Path*, that file will be returned (note that Traditional Path is always unique.)

2. Otherwise, it assumes that the last element in the path is the title, and the other elements of the path are tags. For example ``/photo/abstract/DSC0001`` means: give me a file whose Title is *DSC0001* and that has the *abstract* and *photo* tags. If a **unique** file is found with this query, *toccfs* returns it.

3. If neither of the above matches, *toccfs* assumes that all elements of the path are tags, and returns all the files that have those tags (which can be an empty list).

If the last rule matches, *toccfs* also returns other tags assigned to the files matches with the query. Remember the second example above, where we list the *photo* directory? There are two files that have the *photo* tag in my system, and these files also have the *abstract*,  *landscape*, and *good-shot* tags. *toccfs* returns these tags as directories, to let you browse through the files more easily (i.e. in a graphical file browser like Nautilus, narrowing your query by double clicking on these directories).
