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
   * Removes a tag or a list of tags from a list of files.
   */
  const std::string UNASSIGN_TAGS_SCRIPT =  \
      "$filter_func = function($record) "\
      "{"\
      "  return in_array($record.file_id, $file_ids);"\
      "};"\
      "/* Finding records that should  be updated */"\
      "$records_to_update = db_fetch_all('files', $filter_func); "\
      "foreach ($records_to_update as $record) "\
      "{"\
      "  $record.tags = array_diff($record.tags, $tags_to_unassign);"\
      "  /* Updating the record (removing and adding it again). */"\
      "  db_drop_record('files', $record.__id);"\
      "  db_store('files', $record);"\
      "}";

  // TODO: Find an empty ID instead of max one.
  const std::string CREATE_FILE_SCRIPT = \
      "/* First we gather all files ids in an array"\
      " then we sort that array, and test if they are consecutive."\
      " if an id is not consecutive with the next then it's an empty id */ "\
      "$array_ids = {};"\
      "$record = db_fetch('files');"\
      "while($record != NULL)"\
      "{"\
      "  if ($traditional_path != \"\" && "\
      "    $record.traditional_path == $traditional_path)"\
      "  {"\
      "    $error = \"Error: file with identical traditional path found.\"; "\
      "    exit; "\
      "  }"\
      "  array_push($array_ids, $record.file_id);"\
      "  $record = db_fetch('files');"\
      "}"\

      /* make sure all ids are sorted */
      "sort($array_ids);"\
      "$current_record_id = current($array_ids);"\
      "$previous_record_id = 0;"\
      "while($current_record_id - $previous_record_id == 1)"\
      "{"\
      "  $previous_record_id = $current_record_id;"\
      "  $current_record_id = next($array_ids);"\
      "}"\
      "$new_file = "\
      "{"\
      "  file_id: $previous_record_id + 1,"\
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

  const std::string REMOVE_FILES_SCRIPT = \
      "$founded_files = {};"\
      "$found_something =false;"\
      "while(($record = db_fetch('files')) != NULL)"\
      "{"\
      "  if(in_array($record.file_id, $file_ids))"\
      "  {"\
      "    if(!$found_something)"\
      "    {"\
      "      $found_something = true;"\
      "    }"\
      "    array_push($founded_files, $record);"\
      "    db_drop_record('files', $record.__id);"\
      "  }"\
      "}"\
      "if(!$found_something)"\
      "{"\
      "  $error = 'file(s) doesn t(don t) exist';"\
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

  /*
   * Loops through all the records, and calculates statistics of each tag.
   */
  const std::string COLLECT_TAGS_STATISTICS = \
      "$statistics = {};"\
      " "\
      "$filter_func = function($record) "\
      "{"\
      "  uplink $statistics;"\
      "  /* If file_ids is set, only filter these files. */"\
      "  if ($file_ids)"\
      "  {"\
      "    if (!in_array($record.file_id, $file_ids))"\
      "    {"\
      "      return FALSE;"\
      "    }"\
      "  }"\
      "  if (count($record.tags) == 0)"\
      "  {"\
      "    if (!array_key_exists(\"*no tag*\", $statistics))"\
      "    {"\
      "      $statistics[\"*no tag*\"] = 0;"\
      "    }"\
      "    $statistics[\"*no tag*\"] += 1;"\
      "  }"\
      "  else"\
      "  {"\
      "    foreach ($record.tags as $tag)"\
      "    {"\
      "      if (!array_key_exists($tag, $statistics))"\
      "      {"\
      "        $statistics[$tag] = 0;"\
      "      }"\
      "      $statistics[$tag] += 1;"\
      "    }"\
      "  }"\
      "  return FALSE;"\
      "}; "\
      "db_fetch_all('files', $filter_func);";

  /*
   * Sets a file's title
   */
  const std::string SET_TITLE_SCRIPT = \
      "$found_something = false;"\
      "while(($record = db_fetch('files')) != NULL)"\
      "{"\
      "  if(in_array($record.file_id, $file_ids))"\
      "  {"\
      "    if(!$found_something)"\
      "    {"\
      "      $found_something = true;"\
      "    }"\
      "    /*if the new title isn t the same as the title's file*/"\
      "    if($record.title != $new_title)"\
      "    {"\
      "      $record.title = $new_title;"\
      "      /*Updating the record*/"\
      "      db_drop_record('files', $record.__id);"\
      "      db_store('files', $record);"\
      "    }"\
      "  }"\
      "}"\
      "if(!$found_something)"\
      "{"\
      "  $error = 'Error while trying to set title of file: file ['..$file_id..'] not found.';"\
      "}";
}

#endif /* LIBTOCC_SCRIPTS_H_INCLUDED */
