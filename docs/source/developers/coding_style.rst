
.. highlight:: cpp
  :linenothreshold: 5

.. toctree::
  :hidden:


Coding Style Guid
=================

There are some rules that must be followed by developers of Tocc, in order to
keep a cleaner and more maintainable code.

And remember: Special cases are not special enough to break the rules.


Apperance
---------

* Indents are two spaces.

* Braces should be open in the next line. Example::

    if (name == "test")
    {
      // Do some stuff.
    }

* Never write a ``if``, ``for``, etc without braces::

    // Illegal! Don't write like this.
    if (title.size() == 0)
      title = "default"

* Put spaces around operators, assignments, commas, etc::

    int x = 24;
    int y = 7;
    Point point(x, y * 2);

* There shouldn't be any trailing space in the source file. You can
  use ``git diff --check`` before any commit to check that.


Naming
------

* Never use abbreviation. Always use clear and meaningful name for variables,
  functions, classes, and everything else.

* Name of classes must be in Camel Case. Like ``InvalidArgumentsError``.

* Name of constants must be all in captial letters, and each word separated
  by underscore. Example: ``MAXIMUM_ALLOWED_TAGS = 100``.

* Everything else (methods, variables, name spaces, file names, etc) must be
  all in lower case. Examples: ``tags_list``, ``get_absolute_path``.


Unit Tests
----------

* Developers must write a Unit Test for every functionality they add.


Commit Messages
---------------

* Include related issue number (if any) in the commit message. In the form
  ``issue #52``.

Headers
-------

* First header that includes in a ``.cpp`` file, should be its header. For
  example, in ``expr.cpp``, the first include must be ``expr.h``. Then other
  headers. It will help us see dependency problems earlier.


