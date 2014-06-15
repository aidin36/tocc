/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <aidin@t-o-c-c.com>
 *
 * Tocc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tocc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Tocc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBTOCC_FILE_INFO_H_INCLUDED
#define LIBTOCC_FILE_INFO_H_INCLUDED

#include <ostream>


namespace libtocc
{

  /*
   * Collection of tags.
   */
  class TagsCollection
  {
  public:
    TagsCollection();

    /*
     * @param tags: array to initialize collection with.
     * @param size: size of the array. If passed as zero or
     *   lesser, size will be calculated.
     *
     * @note: It keeps a copy of `tags'.
     */
    TagsCollection(const char* tags[], int size=-1);

    /*
     * Pre-allocates the specified size.
     */
    TagsCollection(int size);

    ~TagsCollection();

    /*
     * Adds a tag to the collection.
     */
    void add_tag(const char* tag);

    /*
     * Removes the specified tag from the collection.
     */
    void remove_tag(const char* tag);

    /*
     * Returns true if the tag exists in the collection.
     */
    bool contains(const char* tag);

    /*
     * Returns number of elements in the collection.
     */
    int size() const;

    /*
     * Returns true if the collection is empty.
     */
    bool is_empty() const;

  private:
    class PrivateData;
    PrivateData* private_data;

  public:

    /*
     * Iterator of the TagsCollection.
     *
     * Example:
     *
     *  TagsCollection tags;
     *  // Add elements to `tags'.
     *  TagsCollection::Iterator iterator(&tags);
     *  for (; !iterator.is_finished(); ++iterator)
     *  {
     *    std::cout << *iterator << std::endl;
     *  }
     */
    class Iterator
    {
    public:
      /*
       * @param collection: Collection to iterate over.
       */
      Iterator(const TagsCollection* collection);

      ~Iterator();

      /*
       * Moves to the next element.
       */
      void next();

      /*
       * Returns true if ends of the iteration reached.
       */
      bool is_finished();

      /*
       * Gets the tag that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      const char* get();

      /*
       * Resets the iterator. (Iterator will be points to the first element).
       */
      void reset();

      /*
       * Moves to the next element.
       */
      Iterator& operator++();

      /*
       * Returns the tag that iterator points to.
       * It will be NULL if iterator passed end of the colleciton.
       */
      const char* operator*();

      /*
       * Returns the tag that iterator points to.
       * It will be NULL if iterator passed end of the colleciton.
       */
      const char* operator->();

    private:
      const TagsCollection* collection;

      class PrivateData;
      PrivateData* private_data;
    };

    // Inside Iterator is a friend of TagsCollection.
    friend class TagsCollection::Iterator;
    friend class FileInfo;
  };


  /*
   * Contains information of a file.
   */
  class FileInfo
  {
  public:
    FileInfo(const char* file_id);

    FileInfo(const char* file_id,
             const char* title,
             const char* traditional_path,
             const char* physical_path);

    FileInfo(const char* file_id,
             const char* title,
             const char* traditional_path,
             const char* physical_path,
             const char* tags[]);

    FileInfo(const char* file_id,
             const char* title,
             const char* traditional_path,
             const char* physical_path,
             const TagsCollection* tags);

    /*
     * Copy constructor.
     */
    FileInfo(const FileInfo& source);

    ~FileInfo();

    /*
     * Gets ID of the file.
     */
    const char* get_id() const;

    /*
     * Gets all the tags of this file.
     */
    TagsCollection get_tags() const;

    /*
     * Gets title of the file.
     */
    const char* get_title() const;

    /*
     * Gets traditional path of the file.
     */
    const char* get_traditional_path() const;

    /*
     * Gets path of the file on the Tocc Managed file system.
     */
    const char* get_physical_path() const;

    /*
     * Overrided operator for std::ostream.
     * So it can be used like:
     *   std::cout << file_info;
     */
    friend std::ostream& operator<<(std::ostream& stream, const FileInfo& file_info);

    /*
     * Assignment operator.
     */
    FileInfo& operator=(const FileInfo& source);

  private:
    class PrivateData;
    PrivateData* private_data;

  };

  class FileInfoCollection
  {
  public:
    /*
     * Creates an empty collection.
     */
    FileInfoCollection();

    /*
     * Creates an empty collection, pre-allocates size.
     */
    FileInfoCollection(int size);

    /*
     * Creates a collection filled with the specified array.
     *
     * @param file_infos: Array to fill the collection with.
     * @param count: Element count of the array. If not specified,
     *   it will calculate the size itself.
     */
    FileInfoCollection(FileInfo file_infos[], int count=-1);

    /*
     * Copy constructor.
     */
    FileInfoCollection(const FileInfoCollection& source);

    ~FileInfoCollection();

    /*
     * Adds a file info the collection.
     *
     * @param file_info: File info to add.
     */
    void add_file_info(FileInfo file_info);

    /*
     * Returns number of elements inside the collection.
     */
    int size();

    /*
     * Returns true if collection have no elements.
     */
    bool is_empty();

    FileInfoCollection& operator=(const FileInfoCollection& source);

  private:
    class PrivateData;
    PrivateData* private_data;

  public:
    /*
     * Iterator of the FileInfoCollection.
     *
     * Example:
     *
     *  FileInfoCollection file_infos;
     *  // Add elements to `file_infos'.
     *  FileInfoCollection::Iterator iterator(&file_infos);
     *  for (; !iterator.is_finished(); ++iterator)
     *  {
     *    std::cout << *iterator << std::endl;
     *  }
     */
    class Iterator
    {
    public:
      /*
       * @param collection: Collection to iterate over.
       */
      Iterator(const FileInfoCollection* collection);

      ~Iterator();

      /*
       * Moves to the next element.
       */
      void next();

      /*
       * Returns true if ends of the iteration reached.
       */
      bool is_finished();

      /*
       * Gets the file info that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      const FileInfo* get();

      /*
       * Resets the iterator. (Iterator will be points to the first element).
       */
      void reset();

      /*
       * Moves to the next element.
       */
      Iterator& operator++();

      /*
       * Returns the file info that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      const FileInfo* operator*();

      /*
       * Returns the file info that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      const FileInfo* operator->();

    private:
      const FileInfoCollection* collection;

      class PrivateData;
      PrivateData* private_data;
    };

    // Inside Iterator is a friend of FileInfoCollection.
    friend class TagsCollection::Iterator;
  };

}

#endif /* LIBTOCC_FILE_INFO_H_INCLUDED */
