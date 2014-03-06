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

#ifndef LIBTOCC_FILE_INFO_CONVERTER_H_INCLUDED
#define LIBTOCC_FILE_INFO_CONVERTER_H_INCLUDED

#include <vector>
#include <string>

#include "common/int_file_info.h"
#include "libtocc.h"

namespace libtocc
{
  FileInfo to_external_file_info(const IntFileInfo* internal_file_info);

  IntFileInfo to_internal_file_info(const FileInfo* external_file_info);

  std::vector<std::string> tags_to_vector(const TagsCollection* collection);

  TagsCollection vector_to_tags(const std::vector<std::string>* vector);

}

#endif /* LIBTOCC_FILE_INFO_CONVERTER_H_INCLUDED */