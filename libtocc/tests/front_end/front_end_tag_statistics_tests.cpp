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


#include <catch.hpp>
#include <fstream>
#include <cstring>

#include "libtocc/front_end/manager.h"
#include "libtocc/front_end/file_info.h"
#include "libtocc/front_end/tag_statistics.h"


TEST_CASE("Tag Statistics: All Tags")
{
  libtocc::Manager manager("/tmp/tocctests/");

  SECTION("Single File")
  {
    /*
     * Preparing test data.
     */
    const char* file_path = "/tmp/tocctests/tocc_statistics_test_file.tmp";

    std::ofstream file_to_import(file_path);
    file_to_import << "some data...";
    file_to_import.close();

    libtocc::FileInfo test_file = manager.import_file(file_path);

    libtocc::TagsCollection tags;
    tags.add_tag("tag_statistics_test_01");

    manager.assign_tags(test_file.get_id(), &tags);

    /*
     * Getting statistics.
     */
    libtocc::TagStatisticsCollection statistics = manager.get_tags_statistics();

    /*
     * Checking result.
     */
    int assigned_files = 0;
    libtocc::TagStatisticsCollection::Iterator iterator(&statistics);
    for (; !iterator.is_finished(); iterator.next())
    {
      if (strcmp(iterator.get().get_tag(), "tag_statistics_test_01") == 0)
      {
        assigned_files = iterator.get().get_assigned_files();
        break;
      }
    }

    REQUIRE(assigned_files == 1);
  }

  SECTION("Multiple Files")
  {
    /*
     * Creating test file.
     */
    const char* file_path = "/tmp/tocctests/tocc_statistics_test_file_ufHf89.tmp";
    std::ofstream file_to_import(file_path);
    file_to_import << "some data...";
    file_to_import.close();

    /*
     * Tags collections to assign to files.
     */
    libtocc::TagsCollection tags_1;
    tags_1.add_tag("tag_statistics_test_02_t01");

    libtocc::TagsCollection tags_2;
    tags_2.add_tag("tag_statistics_test_02_t02");

    /*
     * Importing and assigning tags.
     */
    libtocc::FileInfo test_file_01 =
        manager.import_file(file_path);

    manager.assign_tags(test_file_01.get_id(), &tags_1);

    libtocc::FileInfo test_file_02 =
        manager.import_file(file_path);

    manager.assign_tags(test_file_02.get_id(), &tags_1);
    manager.assign_tags(test_file_02.get_id(), &tags_2);

    libtocc::FileInfo test_file_03 =
        manager.import_file(file_path);

    manager.assign_tags(test_file_03.get_id(), &tags_1);

    /*
     * Checking statistics.
     */
    libtocc::TagStatisticsCollection statistics = manager.get_tags_statistics();

    int tags_1_assigned_files = 0;
    int tags_2_assigned_files = 0;
    libtocc::TagStatisticsCollection::Iterator iterator(&statistics);
    for (; !iterator.is_finished(); iterator.next())
    {
      if (strcmp(iterator.get().get_tag(), "tag_statistics_test_02_t01") == 0)
      {
        tags_1_assigned_files = iterator.get().get_assigned_files();
      }
      if (strcmp(iterator.get().get_tag(), "tag_statistics_test_02_t02") == 0)
      {
        tags_2_assigned_files = iterator.get().get_assigned_files();
      }
    }

    REQUIRE(tags_1_assigned_files == 3);
    REQUIRE(tags_2_assigned_files == 1);
  }
}

TEST_CASE("Tag Statistics: Tags of Files")
{
  libtocc::Manager manager("/tmp/tocctests/");

  /*
   * Creating test file.
   */
  const char* file_path = "/tmp/tocctests/tocc_statistics_test_file_yu78NBq.tmp";
  std::ofstream file_to_import(file_path);
  file_to_import << "some data...";
  file_to_import.close();

  /*
   * Tags collections to assign to files.
   */
  libtocc::TagsCollection tags_1;
  tags_1.add_tag("files_tag_statistics_test_01");

  libtocc::TagsCollection tags_2;
  tags_2.add_tag("files_tag_statistics_test_02");

  /*
   * Importing and assigning tags.
   */
  libtocc::FileInfo test_file_01 =
      manager.import_file(file_path);

  manager.assign_tags(test_file_01.get_id(), &tags_1);

  libtocc::FileInfo test_file_02 =
      manager.import_file(file_path);

  manager.assign_tags(test_file_02.get_id(), &tags_1);
  manager.assign_tags(test_file_02.get_id(), &tags_2);

  /*
   * Checking statistics.
   */
  // Checking both files.
  const char* both_files[2] = { test_file_01.get_id(), test_file_02.get_id() };
  libtocc::TagStatisticsCollection statistics = manager.get_tags_statistics(both_files, 2);

  int tags_1_assigned_files = 0;
  int tags_2_assigned_files = 0;
  libtocc::TagStatisticsCollection::Iterator iterator_1(&statistics);
  for (; !iterator_1.is_finished(); iterator_1.next())
  {
    if (strcmp(iterator_1.get().get_tag(), "files_tag_statistics_test_01") == 0)
    {
      tags_1_assigned_files = iterator_1.get().get_assigned_files();
    }
    if (strcmp(iterator_1.get().get_tag(), "files_tag_statistics_test_02") == 0)
    {
      tags_2_assigned_files = iterator_1.get().get_assigned_files();
    }
  }

  REQUIRE(tags_1_assigned_files == 2);
  REQUIRE(tags_2_assigned_files == 1);

  // Checking first file.
  const char* first_file[1] = { test_file_01.get_id() };
  statistics = manager.get_tags_statistics(first_file, 1);

  tags_1_assigned_files = 0;
  tags_2_assigned_files = 0;
  libtocc::TagStatisticsCollection::Iterator iterator_2(&statistics);
  for (; !iterator_2.is_finished(); iterator_2.next())
  {
    if (strcmp(iterator_2.get().get_tag(), "files_tag_statistics_test_01") == 0)
    {
      tags_1_assigned_files = iterator_2.get().get_assigned_files();
    }
    if (strcmp(iterator_2.get().get_tag(), "files_tag_statistics_test_02") == 0)
    {
      tags_2_assigned_files = iterator_2.get().get_assigned_files();
    }
  }

  REQUIRE(tags_1_assigned_files == 1);
  REQUIRE(tags_2_assigned_files == 0);

  // Checking second file.
  const char* second_file[1] = { test_file_02.get_id() };
  statistics = manager.get_tags_statistics(second_file, 1);

  tags_1_assigned_files = 0;
  tags_2_assigned_files = 0;
  libtocc::TagStatisticsCollection::Iterator iterator_3(&statistics);
  for (; !iterator_3.is_finished(); iterator_3.next())
  {
    if (strcmp(iterator_3.get().get_tag(), "files_tag_statistics_test_01") == 0)
    {
      tags_1_assigned_files = iterator_3.get().get_assigned_files();
    }
    if (strcmp(iterator_3.get().get_tag(), "files_tag_statistics_test_02") == 0)
    {
      tags_2_assigned_files = iterator_3.get().get_assigned_files();
    }
  }

  REQUIRE(tags_1_assigned_files == 1);
  REQUIRE(tags_2_assigned_files == 1);

}
