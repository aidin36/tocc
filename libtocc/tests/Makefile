BUILD_OUTPUT = ../../build/libtocc_tests/
BIN_OUTPUT = ../../bin/
CC = g++
COMPILE_FLAGS = -Wall -fPIC -I../src/ -I. -L$(BIN_OUTPUT) -ltocc -lunqlite $(CFLAGS)

$(BIN_OUTPUT)/tests: main.cpp
	mkdir -p $(BIN_OUTPUT)
	$(CC) main.cpp $(COMPILE_FLAGS) -o $@

runtests: $(BIN_OUTPUT)/tests
	LD_LIBRARY_PATH=$(BIN_OUTPUT) $(BIN_OUTPUT)/tests

clean:
	rm -rf $(BUILD_OUTPUT)
	rm -rf $(BIN_OUTPUT)/tests

