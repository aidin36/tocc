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

#ifndef LIBTOCC_TAGS_STATISTICS_H_INCLUDED
#define LIBTOCC_TAGS_STATISTICS_H_INCLUDED


namespace libtocc
{

  /*
   * Holds statistics of a Tag.
   */
  class TagStatistics
  {
  public:
    TagStatistics(const char* tag, int assigned_tags);

    /*
     * Copy constructor.
     */
    TagStatistics(const TagStatistics& source);

    ~TagStatistics();

    /*
     * Gets the tag.
     */
    const char* get_tag();

    /*
     * Gets number of files assigned to this tag.
     */
    int get_assigned_files();

    /*
     * Assignment operator.
     */
    TagStatistics& operator=(const TagStatistics& source);

  private:
    class PrivateData;
    PrivateData* private_data;
  };


  /*
   * Holds a collection of TagStatistics.
   */
  class TagStatisticsCollection
  {
  public:
    /*
     * Creates an empty collection.
     */
    TagStatisticsCollection();

    /*
     * Creates an empty collection, but reserves `size' before hand.
     */
    TagStatisticsCollection(int size);

    /*
     * Creates a collection with the specified array of statistics.
     *
     * @param statistics: Array to fill the collection with.
     * @param size: Size of the first parameter. If not provided, it will
     *   calculate the size itself. But it's a good idea to provide this
     *   parameter if you have the size in your hand.
     */
    TagStatisticsCollection(TagStatistics statistics[], int size=-1);

    /*
     * Copy constructor.
     */
    TagStatisticsCollection(const TagStatisticsCollection& source);

    ~TagStatisticsCollection();

    /*
     * Adds a statistics to the collection.
     */
    void add_statistics(TagStatistics statistics);


    /*
     * Returns number of elements in the collection.
     */
    int size() const;

    /*
     * Returns `true' if no element is inside the collection.
     */
    bool is_empty() const;

    TagStatisticsCollection& operator=(const TagStatisticsCollection& source);

  private:
    class PrivateData;
    PrivateData* private_data;


  public:

    /*
     * Iterator of TagStatisticsCollection.
     *
     * Example:
     *
     *   TagStatisticsCollection collection;
     *   // Add some elements to the collection.
     *   TagStatisticsCollection::Iterator iterator(&collection);
     *   for (; !iterator.is_finished(); iterator.next())
     *   {
     *     // Do your stuff.
     *   }
     */
    class Iterator
    {
    public:
      /*
       * @param collection: Collection to iterate over.
       */
      Iterator(const TagStatisticsCollection* collection);

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
       * Gets the tag statistics that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      TagStatistics get();

      /*
       * Resets the iterator. (Iterator will be points to the first element).
       */
      void reset();

      /*
       * Moves to the next element.
       */
      Iterator& operator++();

      /*
       * Gets the tag statistics that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      TagStatistics operator*();

      /*
       * Gets the tag statistics that iterator points to.
       * It will be NULL if iterator passed end of the collection.
       */
      TagStatistics operator->();

    private:
      class PrivateData;
      PrivateData* private_data;
    };
  };
}

#endif /* LIBTOCC_TAGS_STATISTICS_H_INCLUDED */
