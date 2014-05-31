
.. default-domain:: standard

.. toctree::
  :hidden:


Tocc's Official CLI Reference
=============================


.. option:: -h, --help

Prints out usage information and exits.

.. option:: -v, --version

Prints out version information and exits.

.. option:: -b, --base-path=PATH

Specify the base path to use (the directory that Tocc keeps its files.)

.. option:: -i, --import=PATH

Imports a file from the traditional file system to the Tocc-managed
file system.

.. option:: -d, --id=ID

Selects a file by its ID.

.. option:: -q, --query=QUERY

Query files. The syntax of query is as follows::

  field operator operand

Some examples::

  # Finds all files that have `book' tag.
  tag = book

  # Finds all files that have both `book' and `programming' tags.
  tag = book and tag = programming

  # Finds files that have `book' tag, and either have a `programming'
  # tag or their titles are equal to "Awesome Book".
  tag = book and (tag = programming or title = "Awesome Book")

.. option:: -p, --print

Prints out the founded files.

.. option:: -a, --assign=TAGS

Assigns tags to files. TAGS is a list of space-separated strings.
some examples::

  tocc --import /media/music/rock/track01.ogg --assign music rock "favorite song"

  tocc --query title = "The Art of Unix Programming" --assign "unix philosophy"


