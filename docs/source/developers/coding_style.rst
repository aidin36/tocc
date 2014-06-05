
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


Naming
------

* Never use abbreviation. Always use clear and meaningful name for variables,
  functions, classes, and everything else.

* Name of classes must be in Camel Case. Like ``InvalidArgumentsError``.

* Name of constants must be all in captial letters, and each word separated
  by underscore. Example: ``MAXIMUM_ALLOWED_TAGS = 100``.

* Everything else (methods, variables, name spaces, file names, etc) must be
  all in lower case. Examples: ``tags_list``, ``get_absolute_path``.


