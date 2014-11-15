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


#include "libtocc/front_end/tag_statistics.h"

#include <string>
#include <vector>


namespace libtocc
{

  class TagStatistics::PrivateData
  {
  public:
    std::string tag;
    int assigned_tags;
  };

  TagStatistics::TagStatistics(const char* tag, int assigned_tags)
  {
    this->private_data = new TagStatistics::PrivateData();

    this->private_data->tag = tag;
    this->private_data->assigned_tags = assigned_tags;
  }

  TagStatistics::TagStatistics(const TagStatistics& source)
  {
    this->private_data = new TagStatistics::PrivateData();
    this->private_data->tag = source.private_data->tag;
    this->private_data->assigned_tags = source.private_data->assigned_tags;
  }

  TagStatistics::~TagStatistics()
  {
    delete this->private_data;
  }

  const char* TagStatistics::get_tag()
  {
    return this->private_data->tag.c_str();
  }

  int TagStatistics::get_assigned_files()
  {
    return this->private_data->assigned_tags;
  }

  TagStatistics& TagStatistics::operator=(const TagStatistics& source)
  {
    if (this == &source)
    {
      return *this;
    }

    this->private_data->tag = source.private_data->tag;
    this->private_data->assigned_tags = source.private_data->assigned_tags;

    return *this;
  }

  class TagStatisticsCollection::PrivateData
  {
  public:
    PrivateData()
    {
    }

    PrivateData(int size)
    {
      this->collection.reserve(size);
    }

    PrivateData(TagStatistics statistics[], int size)
    {
      if (size <= 0)
      {
        size = sizeof(statistics) / sizeof(statistics[0]);
      }

      this->collection.reserve(size);
      this->collection.assign(statistics, statistics + size);
    }

    std::vector<TagStatistics> collection;
  };

  TagStatisticsCollection::TagStatisticsCollection()
  {
    this->private_data = new TagStatisticsCollection::PrivateData();
  }

  TagStatisticsCollection::TagStatisticsCollection(int size)
  {
    this->private_data = new TagStatisticsCollection::PrivateData(size);
  }

  TagStatisticsCollection::TagStatisticsCollection(TagStatistics statistics[], int size)
  {
    this->private_data = new TagStatisticsCollection::PrivateData(statistics, size);
  }

  TagStatisticsCollection::TagStatisticsCollection(const TagStatisticsCollection& source)
  {
    this->private_data = new TagStatisticsCollection::PrivateData();
    this->private_data->collection = source.private_data->collection;
  }

  TagStatisticsCollection::~TagStatisticsCollection()
  {
    delete this->private_data;
  }

  void TagStatisticsCollection::add_statistics(TagStatistics statistics)
  {
    this->private_data->collection.push_back(statistics);
  }

  int TagStatisticsCollection::size() const
  {
    return this->private_data->collection.size();
  }

  bool TagStatisticsCollection::is_empty() const
  {
    return this->private_data->collection.empty();
  }

  TagStatisticsCollection& TagStatisticsCollection::operator=(const TagStatisticsCollection& source)
  {
    if (this == &source)
    {
      return *this;
    }

    this->private_data->collection = source.private_data->collection;

    return *this;
  }

  class TagStatisticsCollection::Iterator::PrivateData
  {
  public:
    const TagStatisticsCollection* collection;

    std::vector<TagStatistics>::iterator collection_iterator;
  };

  TagStatisticsCollection::Iterator::Iterator(const TagStatisticsCollection* collection)
  {
    this->private_data = new TagStatisticsCollection::Iterator::PrivateData();
    this->private_data->collection = collection;
    this->private_data->collection_iterator =
        this->private_data->collection->private_data->collection.begin();
  }

  TagStatisticsCollection::Iterator::~Iterator()
  {
    delete this->private_data;
  }

  void TagStatisticsCollection::Iterator::next()
  {
    this->private_data->collection_iterator++;
  }

  bool TagStatisticsCollection::Iterator::is_finished()
  {
    return (this->private_data->collection_iterator ==
            this->private_data->collection->private_data->collection.end());
  }

  TagStatistics TagStatisticsCollection::Iterator::get()
  {
    return *this->private_data->collection_iterator;
  }

  void TagStatisticsCollection::Iterator::reset()
  {
    this->private_data->collection_iterator =
        this->private_data->collection->private_data->collection.begin();
  }

  TagStatisticsCollection::Iterator& TagStatisticsCollection::Iterator::operator++()
  {
    this->next();
    return *this;
  }

  TagStatistics TagStatisticsCollection::Iterator::operator*()
  {
    return this->get();
  }

  TagStatistics TagStatisticsCollection::Iterator::operator->()
  {
    return this->get();
  }

}
