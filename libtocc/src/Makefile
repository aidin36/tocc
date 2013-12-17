
BUILD_OUTPUT = ../../build/libtocc/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -fPIC -Wall -I. $(CFLAGS)

$(BIN_OUTPUT)/libtocc.so: $(BUILD_OUTPUT)/file_system/file_manager.o $(BUILD_OUTPUT)/common/file_system_exceptions.o $(BUILD_OUTPUT)/database/base23.o
	mkdir -p $(BIN_OUTPUT)
	$(CC) $(COMPILE_FLAGS) -shared $^ -o $@

$(BUILD_OUTPUT)/file_system/file_manager.o: file_system/file_manager.cpp
	mkdir -p $(BUILD_OUTPUT)/file_system/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/common/file_system_exceptions.o: common/file_system_exceptions.cpp
	mkdir -p $(BUILD_OUTPUT)/common/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

$(BUILD_OUTPUT)/database/base23.o: database/base23.cpp
	mkdir -p $(BUILD_OUTPUT)/database/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/libtocc.so
