
.. default-domain:: cpp

.. highlight:: cpp
  :linenothreshold: 3


Reference of *libtocc* API
==========================
Header files of *libtocc* are in ``libtocc`` directory, which itself structured
into the following directories.

* **front_end**: This directory defines the the interface of *libtocc*.
  :cpp:class:`libtocc::Manager` in ``manager.h`` defines the main
  functionalities.

* **exprs**: Expresions for quering files.

libtocc::Manager
----------------

*Available in libtocc/front_end/manager.h*

.. class:: libtocc::Manager(const char* base_path)

To work with *libtocc*, you need to create an instance of this class.

``base_path`` is the absolute path to where Tocc should keep its files. (the
tocc-managed file system.) Note that it have to be absolute.


.. function:: libtocc::FileInfo \
                libtocc::Manager::get_file_info(const char* file_id)

Returns information of a specific file. ``file_id`` is the ID of the file you
want its information. It throw exception if no file with this ID found.

.. function:: libtocc::FileInfo libtocc::Manager::import_file(const char* source_path, \
                const char* title="", \
                const char* traditional_path="")

Copies a file from another file system to tocc-managed file system.

This is the basic way to add a file to tocc-managed file system.

``source_path`` is the absolute path to where the file exists in the
traditional file system. ``title`` is what this file calls, and
``traditional_path`` is a special property that can be set to handle
compatibility with traditional file systems.

Since no tag is passed, a default tag will be assign to the new file.

It returns the information of the newly copied file.

.. function:: libtocc::FileInfo libtocc::Manager::import_file(const char* source_path, \
                const char* title="", \
                const char* traditional_path="", \
                const TagsCollection* tags)

Another overload of ``import_file``. Same as the previous function, but it also
accepts ``tags``. These tags will be assign to the copied file.

.. function:: void libtocc::Manager::assign_tags(const char* file_ids[], \
                int file_ids_size, \
                const TagsCollection* tags)

Assigns a list of tags to a list of files. All of the tags will be assign to
each file.

``file_ids`` is an array of IDs of files to assign tags to. ``file_id_size`` is
the size of the ``file_ids`` array. If you pass zero or a negative number as
``file_id_size``, the method itself will calculate the size. If you have the
size in your hand, it's better to pass it. ``tags`` is the list of tags to
assign to these files.

.. function:: void libtocc::Manager::assign_tags(const char* file_id, const TagsCollection* tags)

Overload of the previous function that accepts a file and a list of tags.

.. function:: void libtocc::Manager::assign_tags(const char* file_id, const char* tag)

Overload of the previous function that accepts a single file and a single tag.

.. function:: void libtocc::Manager::remove_file(const char* file_id)

Removes the file that its ID is ``file_id``.

.. function:: void libtocc::Manager::remove_files(const char* file_ids[], int file_ids_size)

Removes an array of files.

``file_ids`` is an array of IDs of files to remove. ``file_id_size`` is
the size of the ``file_ids`` array. If you pass zero or a negative number as
``file_id_size``, the method itself will calculate the size. If you have the
size in your hand, it's better to pass it.

.. function:: void libtocc::Manager::remove_file(FileInfo& file_to_remove)

Removes the specified file.

.. function:: void libtocc::Manager::remove_files(FileInfoCollection& files_to_remove)

Removes all the files in the specified collection.

.. function:: void libtocc::Manager::set_titles(const char* file_ids[], int file_ids_size, const char* new_title)

Sets the specified title for all of the files in the specified list.

.. function:: void libtocc::Manager::set_title(const char* file_id, const char* new_title)

Sets the specified title to the specified file.


FileInfo Class
--------------

*Available in libtocc/front_end/file_info.h*

.. class:: FileInfo

This class keeps information about a file.

Normally, you don't need to create an instance of this class. This is the
return type of some of the API methods.

.. function:: const char* get_id() const

Returns ID of the file.

.. function:: TagsCollection get_tags() const

Returns a list of tags that are assigned to the file.

.. function:: const char* get_title() const

Returns title of the file.

.. function:: const char* get_traditional_path() const

Returns traditional path of the file.

.. function:: const char* get_physical_path() const

Returns physical path of the file (where file exists on the Tocc-managed
file system).

.. function:: std::ostream& operator<<

This operator will be put a formatted string (in a JSON-like format) of the
class into the ``ostream``. For example, it can be used to print out the
file info::

  libtocc::FileInfo copied_file = manager.import_file("/path/to/file");
  std::cout << copied_file << std::endl;

which will print out something like:

.. code-block:: json

  {
    file_id: 0003a50
    title:
    traditional_path:
    tags: [uncategorized, ]
  }


TagsCollection class
--------------------

This class keeps a list of tags.

*Available in libtocc/front_end/file_info.h*

.. class:: libtocc::TagsCollection
Construct an empty collection.

.. class:: libtocc::TagsCollection(const char* tags[], int size=-1)
Constructs a collection of tags with specified tags in it.

``tags`` is the array of tags to initialize collection with. ``size`` is the
size of the array. If you pass a zero or nagetive number as ``size``, the
method itself calculates the size. But if you have the size in hand, you better
pass it.

.. class:: libtocc::TagsCollection(int size)
Constructs a collection of tags. ``size`` will be reserve.

.. function:: void libtocc::TagsCollection::add_tag(const char* tag)
Adds a tag to the collection.

.. function:: void libtocc::TagsCollection::remove_tag(const char* tag)
Removes the specified tag from the collection.

.. function:: bool libtocc::TagsCollection::contains(const char* tag)
Returns true if the tag exists in the collection.

.. function:: int libtocc::TagsCollection::size() const
Returns number of elements in the collection.

.. function:: bool libtocc::TagsCollection::is_empty() const
Returns true if the collection is empty.


TagsCollection::Iterator class
------------------------------

*Available in libtocc/front_end/file_info.h*

Iterator of the TagsCollection. Usage example::

  TagsCollection tags;
  // Adding some elements to `tags'.
  tags.add("photo");
  tags.add("abstract");

  // Iteratoring over the collection.
  TagsCollection::Iterator iterator(&tags);
  for (; !iterator.is_finished(); ++iterator)
  {
    // Printing out each element.
    std::cout << *iterator << std::endl;
  }


.. class:: libtocc::TagsCollection::Iterator(const libtocc::TagsCollection* collection)
Creates an iterator. ``collection`` is the collection to iterate over.

.. function:: void libtocc::TagsCollection::next()
Moves to the next element. (This also can be done using ``++`` operator.)

.. function:: bool libtocc::TagsCollection::is_finished()
Returns true if ends of the iteration reached.

.. function:: const char* libtocc::TagsCollection::get()
Gets the tag that iterator points to.
It will be NULL if iterator passed end of the collection.
(This method is equal to ``*`` operator.)

.. function:: void libtocc::TagsCollection::reset()
Resets the iterator. (Iterator will be points to the first element).


