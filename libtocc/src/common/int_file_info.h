/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INT_FILE_INFO_H_INCLUDED
#define INT_FILE_INFO_H_INCLUDED

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
    std::vector<std::string> get_tags();

    /*
     * Sets a title for the file.
     */
    void set_title(std::string file_title);

    /*
     * Gets title of the file.
     */
    std::string get_title();

    /*
     * Sets traditional path for the file.
     */
    void set_traditional_path(std::string path);

    /*
     * Gets traditional path of the file.
     */
    std::string get_traditional_path();

  private:
    std::string id;
    std::vector<std::string> tags;
    std::string title;
    std::string traditional_path;
  };

}

#endif /* INT_FILE_INFO_H_INCLUDED */
