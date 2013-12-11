BUILD_OUTPUT = ../../build/libtocc_tests/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -Wall -fPIC -I../src/ -L$(BIN_OUTPUT) -ltocc $(CFLAGS)

tests: file_system/basic_tests.cpp main.cpp
	mkdir -p $(BIN_OUTPUT)
	$(CC) $(COMPILE_FLAGS) main.cpp -o $(BIN_OUTPUT)/$@

runtests: tests
	LD_LIBRARY_PATH=$(BIN_OUTPUT) $(BIN_OUTPUT)/tests

clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/tests

