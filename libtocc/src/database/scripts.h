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

#ifndef LIBTOCC_SCRIPTS_H_INCLUDED
#define LIBTOCC_SCRIPTS_H_INCLUDED

namespace libtocc
{

  /*
   * Creates the `files' collection.
   */
  const std::string COLLECTION_CREATION_SCRIPT = \
    "if (!db_exists('files'))"\
    "{"\
    "  $result = db_create('files');"\
    "  if (!$result)"\
    "  {"\
    "    $error = db_errlog();"\
    "  }"\
    "}";

  /*
   * Appends a tag to the list of tags of a file.
   */
  const std::string ASSIGN_TAGS_SCRIPT =  \
      "$filter_func = function($record) "\
      "{"\
      "  foreach ($file_ids as $file_id)"\
      "  {"\
      "    if ($record.file_id == $file_id)"\
      "    {"\
      "      return TRUE;"\
      "    }"\
      "  }"\
      "  return FALSE;"\
      "};"\
      "/* Finding records that should  be updated */"\
      "$records_to_update = db_fetch_all('files', $filter_func); "\
      "foreach ($records_to_update as $record) "\
      "{"\
      "  foreach ($tags_to_assign as $tag_to_assign)"\
      "  {"\
      "    /* Checking if the tag already exists. */"\
      "    if (!in_array($tag_to_assign, $record.tags))"\
      "    {"\
      "      /* Adding tag to array. */"\
      "      array_push($record.tags, $tag_to_assign);"\
      "      /* Updating the record (removing and adding it again). */"\
      "      db_drop_record('files', $record.__id);"\
      "      db_store('files', $record);"\
      "    }"\
      "  }"\
      "}";

  /*
   * Removes a tag from the list of tags of a file.
   */
  // TODO: Implement this. Right now Unqlite doesn't supports removing an
  //       element from an array. Wait until then, or find a workaround.
  const std::string UNASSIGN_TAGS_SCRIPT =  \
      "";

  // TODO: Find an empty ID instead of max one.
  const std::string CREATE_FILE_SCRIPT = \
      "/* First we find the maximum file ID, then adds a file with an ID"\
      " after that. */ "\
      "$max_id = 0; "\
      "$filter_func = function($record) "\
      "{"\
      "  uplink $max_id;"\
      "  if ($record.file_id > $max_id)"\
      "  {"\
      "    $max_id = $record.file_id;"\
      "  }"\
      "  return false; "\
      "};"\
      "db_fetch_all('files', $filter_func); "\
      "$new_file = "\
      "{"\
      "  file_id: $max_id + 1,"\
      "  title: $title,"\
      "  traditional_path: $traditional_path,"\
      "  tags: $tags "\
      "}; "\
      "$store_result = db_store('files', $new_file); "\
      "if (!$store_result) "\
      "{"\
      "  $error = db_errlog(); "\
      "} "\
      "else "\
      "{"\
      "  $result = $new_file; "\
      "}";

  const std::string GET_FILE_SCRIPT = \
      "/* Manually looping over records, so we can break the loop"\
      " When the file found. */ "\
      "$result = NULL; "\
      "$record = db_fetch('files'); "\
      "while($record != NULL) "\
      "{"\
      "  if ($record.file_id == $file_id)"\
      "  {"\
      "    $result = $record;"\
      "    break;"\
      "  }"\
      "  $record = db_fetch('files'); "\
      "} "\
      "/* If $result does not set, it means file not found. */ "\
      "if ($result == NULL) "\
      "{"\
      "   $error = 'file '..$file_id..' does not exists.'; "\
      "}";
}

#endif /* LIBTOCC_SCRIPTS_H_INCLUDED */
