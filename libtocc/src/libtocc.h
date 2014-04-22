/*
 * This file is part of Tocc. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
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

#ifndef LIBTOCC_LIBTOCC_H_INCLUDED
#define LIBTOCC_LIBTOCC_H_INCLUDED

/*
 * Classes of this file are implemented in the `.cpp' files inside
 * `front_end' directory.
 */

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
             const char* traditional_path);

    FileInfo(const char* file_id,
             const char* title,
             const char* traditional_path,
             const char* tags[]);

    FileInfo(const char* file_id,
             const char* title,
             const char* traditional_path,
             const TagsCollection* tags);

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
     * Overrided operator for std::ostream.
     * So it can be used like:
     *   std::cout << file_info;
     */
    friend std::ostream& operator<<(std::ostream& stream, const FileInfo& file_info);

  private:
    class PrivateData;
    PrivateData* private_data;

  };


  /*
   * The front end of the libtocc.
   */
  class Manager
  {
  public:
    /*
     * @param base_path: Base path of where tocc files kept.
     *   It should be an absolute path.
     */
    Manager(const char* base_path);

    ~Manager();

    /*
     * Gets information of a file.
     */
    FileInfo get_file_info(const char* file_id);

    /*
     * Copies a file from the path to the file system.
     *
     * @param source_path: Path to the source file.
     * @param title: (optional) title of the file.
     * @param traditional_path: (optional) traditional path of the file.
     *
     * @return: Information of the newly created file.
     */
    FileInfo copy_file(const char* source_path,
                       const char* title="",
                       const char* traditional_path="");

    /*
     * Copies a file from the path to the file system.
     *
     * @param source_path: Path to the source file.
     * @param title: title of the file.
     * @param traditional_path: traditional path of the file.
     *   (Can be empty string.)
     * @param tags: Tags to assign to the file.
     *
     * @return: Information of the newly created file.
     */
    FileInfo copy_file(const char* source_path,
                       const char* title,
                       const char* traditional_path,
                       const TagsCollection* tags);

    /*
     * Assigns specified tags to all files in the specified list of files.
     *
     * @param file_ids: Files to assign tags to.
     * @param file_ids_size: size of the `file_ids' array. If set to
     *   zero or less, it will calculated automatically.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(const char* file_ids[],
                     int file_ids_size,
                     const TagsCollection* tags);

    /*
     * Assigns tags to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(const char* file_id, const TagsCollection* tags);

    /*
     * Assigns a tag to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tag: Tag to assign to file.
     */
    void assign_tags(const char* file_id, const char* tag);


  private:
    /*
     * Keeps the private data, and hides it from the client.
     */
    class PrivateData;
    PrivateData* private_data;
  };

}

#endif /* LIBTOCC_LIBTOCC_H_INCLUDED */
