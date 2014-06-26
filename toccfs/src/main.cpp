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

// Using latest FUSE API version.
#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <iostream>

#include "fuse/fuse_interface.h"
#include "engine/fs_handler.h"


using namespace toccfs;


void print_usage()
{
  std::cout << "Usage: toccfs tocc-managed-filesystem mount-point [options]" << std::endl;
}

/*
 * Parses command line arguments.
 *
 * @param argc: Number of elements in `argv'.
 * @param argv: Command line arguments.
 * @param fuse_args: Output parameter. This will be filled with the
 *   modified arguments. It should allocated with [argc - 1] elements.
 *
 * @return: Base path of Tocc-managed file system.
 */
std::string parse_cmd_arguments(int argc, char* argv[], char* fuse_args[])
{
  // First argument is the base path.
  std::string base_path = argv[1];

  // Other arguments should be pass to FUSE.
  fuse_args[0] = argv[0];
  for (int i = 2; i < argc; i++)
  {
    fuse_args[i - 1] = argv[i];
  }

  return base_path;
}

/*
 * Fuse operations structure.
 */
struct fuse_operations operations_struct;


int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Invalid number of arguments." << std::endl;
    print_usage();
    return -20;
  }

  // Initializing Fuse operations structure.
  operations_struct.getattr = getattr;
  operations_struct.readdir = readdir;

  // Initializing our File Syste Handler.
  char* fuse_args[argc - 1];
  std::string base_path = parse_cmd_arguments(argc, argv, fuse_args);

  FSHandler fs_handler(base_path);

  // Running Fuse.
  int fuse_stat = fuse_main(argc - 1, fuse_args, &operations_struct, &fs_handler);

  return fuse_stat;
}
