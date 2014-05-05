## Makefile.am -- Process this file with automake to produce Makefile.in

# Output and source files.
lib_LTLIBRARIES = libtocc.la
# Refer to this chapter of Libtool Manual for understanding versioning rules:
# http://www.gnu.org/software/libtool/manual/html_node/Versioning.html
libtocc_la_LDFLAGS = -version-info 0:0:0
libtocc_la_SOURCES = check_exists.cpp common/database_exceptions.cpp common/expr_exceptions.cpp common/file_system_exceptions.cpp common/int_file_info.cpp utilities/file_info_converter.cpp database/base23.cpp database/database.cpp database/exprs/compiled_expr.cpp database/exprs/compiler.cpp database/exprs/connectives.cpp database/exprs/fields.cpp database/exprs/functions.cpp database/exprs/operands.cpp database/exprs/query.cpp file_system/file_manager.cpp engine/files_engine.cpp engine/tags_engine.cpp front_end/file_info.cpp front_end/manager.cpp

# Installing headers
library_includedir=$(includedir)/libtocc/
library_include_HEADERS = front_end/file_info.h front_end/manager.h common/base_exception.h common/database_exceptions.h common/expr_exceptions.h common/file_system_exceptions.h common/runtime_exceptions.h database/exprs/expr.h database/exprs/connectives.h database/exprs/fields.h database/exprs/functions.h database/exprs/operands.h database/exprs/query.h

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = libtocc.pc

