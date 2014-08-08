## Makefile.am -- Process this file with automake to produce Makefile.in

# Output and source files.
bin_PROGRAMS = toccfs
toccfs_SOURCES = utils/string_utils.cpp fuse/fuse_interface.cpp engine/fs_handler.cpp main.cpp
toccfs_LDADD = @FUSE_LIBS@
toccfs_CXXFLAGS = @FUSE_CFLAGS@

