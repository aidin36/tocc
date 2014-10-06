Tocc File System (toccfs)
-----------------------------------------

Tocc stores all the files in a special structure, and let other applications query and use the files using its API. It means, if any application wants to use files stored using Tocc, it should know how to talk with Tocc. It's not possible in all cases. (At least, not untill Tocc become famous enough that everyone supports it ;-) )

To solve this, to let other applications use files stored with Tocc, there's a special File System available: *toccfs*

*toccfs* looks like normal file Systems: you mount it somewhere, and then you can see your files like they stored in a traditional file system: in a tree of direcories and files.

I this way, any other applications that can only understand traditional way of storing files, can use Tocc without any change. You can browse your files using *Nautilus*, even you can acess them on network using *Samba*, and like that.


How to Use
-------------------

First, mount your *Tocc Managed File System* somewhere::

  $ toccfs /home/tocc-managed/ /mnt/traditional-acess/

First argument is the path to *Tocc Managed File System* (where Tocc stores its files, the *base path* you pass to CLI when working with it.) The second argument is the mount point.

Now, you can acess your files from ``/mnt/traditional-acess/`` using every tool you want. For example::

  $ ls /mnt/traditional-acess/
     photo  good-shot   landscape  abstract  document  my-cv

  $ ls /mnt/traditional-acess/photo/
     abstract  landscape  good-shot  DSC0001  DSC0002  DSC0003

But wait a minute! What happened?

In order to map sturcture of *Files and Tags* to *Directories and Files*, *toccfs* shows each tag as a directory, and each file that have tha tag, as a file inside that directory.

Let's explain it with an example.

If you list files inside ``/mnt/traditional-acess/photo/abstract/``, it means you asked Tocc to give you all the files that tagged *photo* and *abstract*. Or if you get ``/mnt/traditional-acess/photo/DSC00001``, it means you asked Tocc to give you a file tagged *photo* and its Title is *DSC0001*.

In other word, each path is a query to Tocc.

Now that you find out how it works, let me tell you the rules of the query language. When pass a path to *toccfs*, it compiles it as follows:

1. If it matches exactly with a *Traditional Path*, that file will return (note that Traditional Path is always unique.)

2. It assumes that the last element in the path is the title, and other elemnts of path are tags. For example ``/photo/abstract/DSC0001`` maps to: give me a file that its Title is *DSC0001* and have *abstract* and *photo* tags. If a **unique** file found with this query, it returns it.

3. If none of the above matches, it assume that every element of path is a tag, and returns all the files that have those tags.

If the last rule matches, *toccfs* also returns other tags assigned to the files matches with the query. Remember the second example above? When we list *photo* directory? There's two files that have *photo* tag in my system, and these files also had *abstract*,  *landscape*, and *good-shot* tags. *toccfs* returns these tags as directories, to let you browse through the files more easily (i.e. in a graphical file browser like Nautilus, narrowing your query by double clicking on these directories.)

