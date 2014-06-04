## Makefile.am -- Process this file with automake to produce Makefile.in

# Output and source files.
lib_LTLIBRARIES = libtocc.la
# Refer to this chapter of Libtool Manual for understanding versioning rules:
# http://www.gnu.org/software/libtool/manual/html_node/Versioning.html
libtocc_la_LDFLAGS = -version-info 0:0:0
libtocc_la_SOURCES = libtocc/check_exists.cpp libtocc/common/database_exceptions.cpp libtocc/common/expr_exceptions.cpp libtocc/common/file_system_exceptions.cpp libtocc/common/int_file_info.cpp libtocc/utilities/file_info_converter.cpp libtocc/utilities/file_utils.cpp libtocc/database/base23.cpp libtocc/database/database.cpp libtocc/exprs/compiled_expr.cpp libtocc/exprs/compiler.cpp libtocc/exprs/connectives.cpp libtocc/exprs/fields.cpp libtocc/exprs/functions.cpp libtocc/exprs/operands.cpp libtocc/exprs/query.cpp libtocc/file_system/file_manager.cpp libtocc/engine/files_engine.cpp libtocc/engine/tags_engine.cpp libtocc/front_end/file_info.cpp libtocc/front_end/tag_statistics.cpp libtocc/front_end/manager.cpp

# Installing headers
front_end_includedir = $(includedir)/libtocc/front_end
front_end_include_HEADERS = libtocc/front_end/file_info.h libtocc/front_end/manager.h
common_includedir = $(includedir)/libtocc/common/
common_include_HEADERS = libtocc/common/base_exception.h libtocc/common/database_exceptions.h libtocc/common/expr_exceptions.h libtocc/common/file_system_exceptions.h libtocc/common/runtime_exceptions.h
exprs_includedir = $(includedir)/libtocc/exprs/
exprs_include_HEADERS = libtocc/exprs/expr.h libtocc/exprs/connectives.h libtocc/exprs/fields.h libtocc/exprs/functions.h libtocc/exprs/operands.h libtocc/exprs/query.h libtocc/exprs/compiled_expr_types.h

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = libtocc.pc

# Libtool doesn't update ld's cache by default. This hook is added to ensure
# that cache is updated after library is installed. Though it make the
# installation a little slow.
# Also, I ignored the errors. Because there maybe no `ldconfig' on the system
# or corrent user don't have access to execute it.
install-exec-hook:
	-ldconfig

