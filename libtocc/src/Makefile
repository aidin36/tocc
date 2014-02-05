
BUILD_OUTPUT = ../../build/libtocc/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -fPIC -Wall -I. $(CFLAGS)
BOOST_FLAG =

# If user provided a custom path for boost.
ifneq ($(strip $(BOOST_PATH)),)
BOOST_FLAG = -I $(BOOST_PATH)
endif

$(BIN_OUTPUT)/libtocc.so: $(BUILD_OUTPUT)/file_system/file_manager.o $(BUILD_OUTPUT)/common/file_system_exceptions.o $(BUILD_OUTPUT)/common/database_exceptions.o $(BUILD_OUTPUT)/common/expr_exceptions.o $(BUILD_OUTPUT)/database/base23.o $(BUILD_OUTPUT)/database/database.o $(BUILD_OUTPUT)/database/exprs/connectives.o $(BUILD_OUTPUT)/database/exprs/functions.o $(BUILD_OUTPUT)/database/exprs/operands.o $(BUILD_OUTPUT)/database/exprs/fields.o $(BUILD_OUTPUT)/database/exprs/compiled_expr.o $(BUILD_OUTPUT)/database/exprs/compier.o $(BUILD_OUTPUT)/database/exprs/query.o
	mkdir -p $(BIN_OUTPUT)
	$(CC) $(COMPILE_FLAGS) -shared $^ -o $@

$(BUILD_OUTPUT)/file_system/file_manager.o: file_system/file_manager.cpp
	mkdir -p $(BUILD_OUTPUT)/file_system/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/common/file_system_exceptions.o: common/file_system_exceptions.cpp
	mkdir -p $(BUILD_OUTPUT)/common/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/common/database_exceptions.o: common/database_exceptions.cpp
	mkdir -p $(BUILD_OUTPUT)/common/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/common/expr_exceptions.o: common/expr_exceptions.cpp
	mkdir -p $(BUILD_OUTPUT)/common/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/base23.o: database/base23.cpp
	mkdir -p $(BUILD_OUTPUT)/database/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/database.o: database/database.cpp
	mkdir -p $(BUILD_OUTPUT)/database/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/connectives.o: database/exprs/connectives.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) $(BOOST_FLAG) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/functions.o: database/exprs/functions.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) $(BOOST_FLAG) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/operands.o: database/exprs/operands.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) $(BOOST_FLAG) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/fields.o: database/exprs/fields.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) $(BOOST_FLAG) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/compiled_expr.o: database/exprs/compiled_expr.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/compier.o: database/exprs/compiler.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/exprs/query.o: database/exprs/query.cpp
	mkdir -p $(BUILD_OUTPUT)/database/exprs/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@


clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/libtocc.so
