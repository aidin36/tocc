BUILD_OUTPUT = ../../build/libtocc_tests/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -Wall -fPIC -I../src/ -L$(BIN_OUTPUT) -ltocc $(CFLAGS)

$(BIN_OUTPUT)/tests: file_system/basic_tests.cpp main.cpp
	mkdir -p $(BIN_OUTPUT)
	$(CC) $(COMPILE_FLAGS) main.cpp -o $@

runtests: $(BIN_OUTPUT)/tests
	LD_LIBRARY_PATH=$(BIN_OUTPUT) $(BIN_OUTPUT)/tests

clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/tests

