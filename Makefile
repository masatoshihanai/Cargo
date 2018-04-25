CC = gcc -O3 -g -c -Iinclude -o $@
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 -O3 -g -c -Iinclude -o $@
#-------------------------------------------------------------------------------
OBJECTS = \
		  build/simulator.o \
		  build/gtree.o \
		  build/file.o \
		  build/sqlite3.o
lib/libcargo.a: $(OBJECTS)
	ar rcs $@ $^
#-------------------------------------------------------------------------------
$(OBJECTS): | build

build/simulator.o: \
	include/libcargo/simulator.h \
	include/libcargo/types.h \
	include/libcargo/file.h \
	include/libcargo/options.h \
	include/libcargo/message.h \
	include/gtree/gtree.h \
	include/sqlite3/sqlite3.h \
	src/simulator.cpp
	$(CXX) $(CFLAGS) src/simulator.cpp

build/gtree.o: \
	include/gtree/gtree.h \
	src/gtree/gtree.cpp
	$(CXX) $(CFLAGS) src/gtree/gtree.cpp

build/file.o: \
	include/libcargo/file.h \
	src/file.cpp
	$(CXX) $(CFLAGS) src/file.cpp

build/sqlite3.o: \
	include/sqlite3/sqlite3.h \
	src/sqlite3/sqlite3.c
	$(CC) src/sqlite3/sqlite3.c

build:
	mkdir -p build

clean:
	rm -rf build/ lib/libcargo.a