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

#ifndef TOCCFS_FUSE_INTERFACE_H_INCLUDED
#define TOCCFS_FUSE_INTERFACE_H_INCLUDED

// Using latest FUSE API version.
#define FUSE_USE_VERSION 26

#include <fuse.h>


namespace toccfs
{

  int getattr(const char* path, struct stat* stbuf);

  int readdir(const char* path, void* buffer, fuse_fill_dir_t filler,
              off_t offset, struct fuse_file_info* fileinfo);
}

#endif /* TOCCFS_FUSE_INTERFACE_H_INCLUDED */
