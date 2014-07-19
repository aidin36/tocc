
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

This option accepts a formatting. If you don't pass any arguments to it, it
will print out title of each file. Here's an example of a custom format::

  --print {id}, {physical_path}: {title}

Output is something like::

  0000012, /opt/tocc-managed/0/00/00/12: Track01

Arguments between braces are replaced with the file's information. All the
other characters prints out same as they inputed. Here some other examples::

  --print ({id}) -> {physical_path}
  # Outputs: (0000012) -> /opt/tocc-managed/0/00/00/12

  # To escape a brace, write it twice.
  --print {{ID: {id}, Name: {title}}}
  # Outputs: {ID: 0000012, Name: Track01}

These fields can be use in the ``--print`` option.

* id: ID of the file.
* title: Title of the file.
* physical_path: Path to where the file located on disk.
* traditional_path: Traditional path of the file.
* tags: List of file's tags.


.. option:: -a, --assign=TAGS

Assigns tags to files. TAGS is a list of space-separated strings.
some examples::

  tocc --import /media/music/rock/track01.ogg --assign music rock "favorite song"

  tocc --query title = "The Art of Unix Programming" --assign "unix philosophy"

.. option:: -r, --remove

Removes files.

Example::

  tocc --query tag = useless --remove

Which removes all the files tagged *useless*.

.. option:: -t, --set-title=TITLE

Sets title of files. For example::

  # Setting title of the file with 0013a4b ID to Archive01
  tocc --id 0013a4b --set-title Archive01

  # Setting title of all files tagged photo and 2014-03-07, to "A Jungle Trip".
  tocc --query tag = photo and tag = 2014-03-07 --set-title "A Jungle Trip"


