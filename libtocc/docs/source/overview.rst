
Design Overview
===============

.. TODO Add design-overview.png image here.

Engine of the Tocc is *libtocc*. Everything is implemented in it. Other
components are interfaces that works with it. i.e. *tocc* CLI, *toccfs*,
and other UIs that is written for Tocc.

All the user's files store in a real file system (i.e. an Ext4 file system).
Files will rename to codes, and will be store in a specific structure.
There's a database that contains information about each file: Its tags, title,
and other properties of the file.

To understand it, consider the following scenario.

When user wants to store a file in Tocc system, it will call ``copy`` method
of the *libtocc* API. The file itself copies to the real file system (Ext4
in our example), and a record will be store in the database containing the file
information. Then, user assign some tags to the file by calling ``assign_tag``
method. File's record in database will be updated and those tags will be added
to it. Now, user can query files by calling ``query`` method of the API.
*libtocc* will search its database to see which files will match with the query,
and return them.
