
BUILD_OUTPUT = ../../build/libtocc/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -fPIC -Wall -I. $(CFLAGS)

libtocc.so: file_system/file_manager.o
	mkdir -p $(BIN_OUTPUT)
	$(CC) $(COMPILE_FLAGS) -shared $(BUILD_OUTPUT)/$^ -o $(BIN_OUTPUT)/$@

file_system/file_manager.o: file_system/file_manager.cpp
	mkdir -p $(BUILD_OUTPUT)/file_system/
	$(CC) $(COMPILE_FLAGS) -c $^ -o $(BUILD_OUTPUT)/$@

clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/libtocc.so
