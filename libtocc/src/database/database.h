/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
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

#ifndef LIBTOCC_DATABASE_H_INCLUDED
#define LIBTOCC_DATABASE_H_INCLUDED

#include <string>
#include <list>

// Forward declaration of unqlite. So I don't have to include the
// unqlite.h in my header, so it will be hidden from the others
// who include this header.
struct unqlite;

namespace libtocc
{

  /*
   * NOTE: Each instance of this class holds a handler of the database file
   * specified in constructor. So, you can't have two instances of this
   * class with the same database file. (Unqlite locks the database file
   * and will raise an exception if file opens twice.)
   */
  class Database
  {
  public:
    /*
     * Constructor.
     * @param database_file: database to work with.
     */
    Database(std::string database_file);
    
    ~Database();

    /*
     * Adds a file to the database.
     */
    void add_file(std::string file_id);

    /*
     * Assigns specified tags to each specified file.
     */
    void assign_tag(std::list<std::string> file_ids,
                    std::list<std::string> tags);

    /*
     * Assigns specified tags to the file.
     */
    void assign_tag(std::string file_id,
                    std::list<std::string> tags);

    /*
     * Assigns a tag to a file.
     */
    void assign_tag(std::string file_id, std::string tag);

    /*
     * Unassign a tag from a file.
     */
    void unassign_tag(std::string file_id, std::string tag);

  private:
    /*
     * Database handler.
     */
    unqlite* db_pointer;

  };

};

#endif /* LIBTOCC_DATABASE_H_INCLUDED */
