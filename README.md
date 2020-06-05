Tocc, a Tool for Obsessive Compulsive Classifiers
================================================

Introduction
------------

Tocc is a tag-based file management system. It also includes a tag-based file
system called Toccfs. The goal of Tocc is to provide a better system for
classifying files which is more flexible than classic file systems based on a
tree of files and directories.

For more information about why Tocc was created, whether you need it, its vision, and
what it can be used for, take a look at its web page:

   https://tocc.aidinhut.com

Copyright
---------
Tocc is free software and is released under the terms of Gnu General Public
License version 3. Refer to COPYING file for the full license.

Building Source
---------------
Tocc consist of three components: ``libtocc``, ``cli`` and ``toccfs``.
``libtocc`` is the heart of the system. ``cli`` and ``toccfs`` are two
interfaces for the Tocc system.

[How to compile libtocc](https://tocc.aidinhut.com/libtocc/compile.html)

[How to compile cli](https://tocc.aidinhut.com/cli/compile.html)

[How to compile toccfs](https://tocc.aidinhut.com/toccfs/compile.html)

Building Documents
------------------
If you get the source code from the Github repository, only the source of the
documents is available. To build them, you need *Sphinx*. You can either
install it from your distro's package manager, or get it from its website:

   http://sphinx-doc.org/

Then, go to `docs` directory in the root and inside each directory of the
repository and run `make html`. Then, you can find the documentation as HTML
files in the `build\html` directory inside the `docs`.

Contact
-------
Currently, Tocc is maintain by Aidin Gharibnavaz. You can contact him at the
following e-mail address:

   aidin (at) aidinhut (dot) com

You can find the development team by visiting Tocc's Github page:

   https://github.com/aidin36/tocc/
