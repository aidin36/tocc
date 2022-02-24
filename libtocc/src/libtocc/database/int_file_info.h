/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidinhut.com>
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

#ifndef LIBTOCC_INT_FILE_INFO_H_INCLUDED
#define LIBTOCC_INT_FILE_INFO_H_INCLUDED

/*
 * Defines two classes: One is Internal File Info, and other one is
 * Internal File Info Collection which is a collection of the first one.
 */

#include <string>
#include <vector>

namespace libtocc
{

  /*
   * Keeps information about a file.
   * This class is internal and only accessible inside the library.
   * Interface methods should use FileInfo class.
   */
  class IntFileInfo
  {
  public:
    IntFileInfo(std::string file_id);

    IntFileInfo(std::string file_id,
                std::string title,
                std::string traditional_path,
                std::vector<std::string> tags);

    /*
     * Copy constructor.
     */
    IntFileInfo(const IntFileInfo& source);

    /*
     * Gets ID of the file.
     */
    std::string get_id() const;

    /*
     * Sets a list of tags to file.
     * Note that it replace old ones.
     */
    void set_tags(std::vector<std::string> new_tags);

    /*
     * Add a single tag to file.
     */
    void add_tag(std::string new_tag);

    /*
     * Gets all the tags of this file.
     */
    std::vector<std::string> get_tags() const;

    /*
     * Sets a title for the file.
     */
    void set_title(std::string file_title);

    /*
     * Gets title of the file.
     */
    std::string get_title() const;

    /*
     * Sets traditional path for the file.
     */
    void set_traditional_path(std::string path);

    /*
     * Gets traditional path of the file.
     */
    std::string get_traditional_path() const;

    /*
     * Returns a string representation of the file.
     */
    std::string to_string() const;

    /*
     * Overrided operator for std::ostream.
     * So it can be used like:
     *   std::cout << file_info;
     */
    friend std::ostream& operator<<(std::ostream& stream, const IntFileInfo& file_info);

    /*
     * Assignment operator.
     */
    IntFileInfo& operator=(const IntFileInfo& source);

  private:
    std::string id;
    std::vector<std::string> tags;
    std::string title;
    std::string traditional_path;
  };
}

#endif /* LIBTOCC_INT_FILE_INFO_H_INCLUDED */
