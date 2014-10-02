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

#include "libtocc/front_end/file_info.h"

#include <string>
#include <cstring>
#include <iostream> // for std::endl
#include <vector>


namespace libtocc
{

  /*
   * Private data of TagsCollection.
   */
  class TagsCollection::PrivateData
  {
  public:

    PrivateData()
    {
    }

    /*
     * @param tags: array to initialize collection with.
     * @param size: size of the array. If passed as zero or
     *   lesser, size will be calculated.
     */
    PrivateData(const char* tags[], int size)
    {
      if (size <= 0)
      {
        size = sizeof(tags) / sizeof(tags[0]);
      }

      this->tags.reserve(size);
      this->tags.assign(tags, tags + size);
    }

    /*
     * Pre-allocates the specified size.
     */
    PrivateData(int size)
    {
      this->tags.reserve(size);
    }

    /*
     * Collection of tags.
     */
    std::vector<std::string> tags;
  };

  TagsCollection::TagsCollection()
  {
    this->private_data = new PrivateData();
  }

  TagsCollection::TagsCollection(const char* tags[], int size)
  {
    this->private_data = new PrivateData(tags, size);
  }

  TagsCollection::TagsCollection(int size)
  {
    this->private_data = new PrivateData(size);
  }

  TagsCollection::~TagsCollection()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  void TagsCollection::add_tag(const char* tag)
  {
    this->private_data->tags.push_back(tag);
  }

  void TagsCollection::remove_tag(const char* tag)
  {
    std::vector<std::string>::iterator iterator =
        this->private_data->tags.begin();

    for(; iterator != this->private_data->tags.end(); ++iterator)
    {
      if (*iterator == tag)
      {
        this->private_data->tags.erase(iterator);
        break;
      }
    }
  }

  bool TagsCollection::contains(const char* tag)
  {
    std::vector<std::string>::iterator iterator =
        this->private_data->tags.begin();

    for(; iterator != this->private_data->tags.end(); ++iterator)
    {
      if (*iterator == tag)
      {
        return true;
      }
    }

    return false;
  }

  int TagsCollection::size() const
  {
    return this->private_data->tags.size();
  }

  bool TagsCollection::is_empty() const
  {
    return this->private_data->tags.empty();
  }

  class TagsCollection::Iterator::PrivateData
  {
  public:
    std::vector<std::string>::iterator collection_iterator;
  };

  TagsCollection::Iterator::Iterator(const TagsCollection* collection)
  {
    this->collection = collection;

    this->private_data = new PrivateData();
    this->private_data->collection_iterator =
        this->collection->private_data->tags.begin();
  }

  TagsCollection::Iterator::~Iterator()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  void TagsCollection::Iterator::next()
  {
    ++this->private_data->collection_iterator;
  }

  bool TagsCollection::Iterator::is_finished()
  {
    return (this->private_data->collection_iterator ==
            this->collection->private_data->tags.end());
  }

  const char* TagsCollection::Iterator::get()
  {
    return (*this->private_data->collection_iterator).c_str();
  }

  void TagsCollection::Iterator::reset()
  {
    this->private_data->collection_iterator =
        this->collection->private_data->tags.begin();
  }

  TagsCollection::Iterator& TagsCollection::Iterator::operator++()
  {
    this->next();
    return *this;
  }

  const char* TagsCollection::Iterator::operator*()
  {
    return this->get();
  }

  const char* TagsCollection::Iterator::operator->()
  {
    return this->get();
  }


  class FileInfo::PrivateData
  {
  public:
    std::string file_id;
    std::string title;
    std::string traditional_path;
    std::string physical_path;
    std::vector<std::string> tags;
  };

  FileInfo::FileInfo(const char* file_id)
  {
    this->private_data = new PrivateData();
    this->private_data->file_id = file_id;
    this->private_data->title = "";
    this->private_data->traditional_path = "";
    this->private_data->physical_path = "";
  }

  FileInfo::FileInfo(const char* file_id,
                     const char* title,
                     const char* traditional_path,
                     const char* physical_path)
  {
    this->private_data = new PrivateData();
    this->private_data->file_id = file_id;
    this->private_data->title = title;
    this->private_data->traditional_path = traditional_path;
    this->private_data->physical_path = physical_path;
  }

  FileInfo::FileInfo(const char* file_id,
                     const char* title,
                     const char* traditional_path,
                     const char* physical_path,
                     const char* tags[])
  {
    this->private_data = new PrivateData();
    this->private_data->file_id = file_id;
    this->private_data->title = title;
    this->private_data->traditional_path = traditional_path;
    this->private_data->physical_path = physical_path;

    this->private_data->tags.assign(tags, tags + (sizeof(tags) / sizeof(tags[0])));
  }

  FileInfo::FileInfo(const char* file_id,
                     const char* title,
                     const char* traditional_path,
                     const char* physical_path,
                     const TagsCollection* tags)
  {
    this->private_data = new PrivateData();
    this->private_data->file_id = file_id;
    this->private_data->title = title;
    this->private_data->traditional_path = traditional_path;
    this->private_data->physical_path = physical_path;
    this->private_data->tags = tags->private_data->tags;
  }

  FileInfo::FileInfo(const FileInfo& source)
  {
    this->private_data = new PrivateData();
    this->private_data->file_id = source.private_data->file_id;
    this->private_data->title = source.private_data->title;
    this->private_data->traditional_path = source.private_data->traditional_path;
    this->private_data->physical_path = source.private_data->physical_path;
    this->private_data->tags = source.private_data->tags;
  }

  FileInfo::~FileInfo()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  const char* FileInfo::get_id() const
  {
    return this->private_data->file_id.c_str();
  }

  TagsCollection FileInfo::get_tags() const
  {
    TagsCollection result;
    result.private_data->tags = this->private_data->tags;
    return result;
  }

  const char* FileInfo::get_title() const
  {
    return this->private_data->title.c_str();
  }

  const char* FileInfo::get_traditional_path() const
  {
    return this->private_data->traditional_path.c_str();
  }

  const char* FileInfo::get_physical_path() const
  {
    return this->private_data->physical_path.c_str();
  }

  std::ostream& operator<<(std::ostream& stream, const FileInfo& file_info)
  {
    stream << "{" << std::endl;
    stream << "  file_id: " << file_info.get_id() << std::endl;
    stream << "  title: " << file_info.get_title() << std::endl;
    stream << "  traditional_path: " << file_info.get_traditional_path() << std::endl;
    stream << "  physical_path: " << file_info.get_physical_path() << std::endl;
    stream << "  tags: [";

    std::vector<std::string>::iterator iterator =
        file_info.private_data->tags.begin();

    for (; iterator != file_info.private_data->tags.end(); ++iterator)
    {
      stream << *iterator << ", ";
    }

    stream << "]" << std::endl;

    stream << "}";

    return stream;
  }

  FileInfo& FileInfo::operator=(const FileInfo& source)
  {
    if (this == &source)
    {
      return *this;
    }

    this->private_data->file_id = source.private_data->file_id;
    this->private_data->title = source.private_data->title;
    this->private_data->traditional_path = source.private_data->traditional_path;
    this->private_data->physical_path = source.private_data->physical_path;
    this->private_data->tags = source.private_data->tags;

    return *this;
  }

  class FileInfoCollection::PrivateData
  {
  public:
    PrivateData()
    {
    }

    PrivateData(int size)
    {
      file_infos.reserve(size);
    }

    PrivateData(FileInfo file_infos[], int count)
    {
      if (count <= 0)
      {
        count = sizeof(file_infos) / sizeof(file_infos[0]);
      }

      this->file_infos.reserve(count);
      this->file_infos.assign(file_infos, file_infos + count);
    }

    PrivateData(std::vector<FileInfo> file_infos)
    {
      this->file_infos = file_infos;
    }

    std::vector<FileInfo> file_infos;
  };

  FileInfoCollection::FileInfoCollection()
  {
    this->private_data = new PrivateData();
  }

  FileInfoCollection::FileInfoCollection(int size)
  {
    this->private_data = new PrivateData(size);
  }

  FileInfoCollection::FileInfoCollection(FileInfo file_infos[], int count)
  {
    this->private_data = new PrivateData(file_infos, count);
  }

  FileInfoCollection::FileInfoCollection(const FileInfoCollection& source)
  {
    this->private_data = new PrivateData(source.private_data->file_infos);
  }

  FileInfoCollection::~FileInfoCollection()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  void FileInfoCollection::add_file_info(FileInfo file_info)
  {
    this->private_data->file_infos.push_back(file_info);
  }

  int FileInfoCollection::size()
  {
    return this->private_data->file_infos.size();
  }

  bool FileInfoCollection::is_empty()
  {
    return this->private_data->file_infos.empty();
  }

  FileInfoCollection& FileInfoCollection::operator=(const FileInfoCollection& source)
  {
    if (this == &source)
    {
      return *this;
    }

    this->private_data->file_infos = source.private_data->file_infos;
    return *this;
  }

  class FileInfoCollection::Iterator::PrivateData
  {
  public:
    std::vector<FileInfo>::iterator collection_iterator;
  };

  FileInfoCollection::Iterator::Iterator(const FileInfoCollection* collection)
  {
    this->collection = collection;

    this->private_data = new PrivateData();
    this->private_data->collection_iterator =
        this->collection->private_data->file_infos.begin();
  }

  FileInfoCollection::Iterator::~Iterator()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  void FileInfoCollection::Iterator::next()
  {
    ++this->private_data->collection_iterator;
  }

  bool FileInfoCollection::Iterator::is_finished()
  {
    return (this->private_data->collection_iterator ==
            this->collection->private_data->file_infos.end());
  }

  const FileInfo* FileInfoCollection::Iterator::get()
  {
    return &(*this->private_data->collection_iterator);
  }

  void FileInfoCollection::Iterator::reset()
  {
    this->private_data->collection_iterator =
        this->collection->private_data->file_infos.begin();
  }

  FileInfoCollection::Iterator& FileInfoCollection::Iterator::operator++()
  {
    this->next();
    return *this;
  }

  const FileInfo* FileInfoCollection::Iterator::operator*()
  {
    return this->get();
  }

  const FileInfo* FileInfoCollection::Iterator::operator->()
  {
    return this->get();
  }

}
