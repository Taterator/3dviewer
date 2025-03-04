CC = g++
CFLAGS = -c -Wall -Werror -Wextra -std=c++17
FLAGS = -Wall -Werror -Wextra -std=c++17
LIBRARIES=-lgtest -lgmock -pthread
TEST_FLAGS=--coverage $(LIBRARIES)
SRC = *.cc
TEST_SOURCES=./3DViewerBack/object3d.cc
TEST_FILE=model_tests
OS = $(shell uname)

BUILD_FILE_TEMP = 3DViewer_v2
BUILD_FILE = 3DViewer_v2
OPEN = xdg-open

_SRC = .cc
_LIB = .a
_OBJ = .o

EXECUT = test_ex

TEST_DIR = ./test
TEMP_DIR = ./temp
GCOV_DIR = ./report
BUILD_DIR = ../build
DIST_DIR = ./3DViewer_v2
HTML_DIR = docs

QUIET = GNUMAKEFLAGS=--no-print-directory

DIST_DIR = ./"3DViewer_v2.0"
HTML_DIR = docs
DIST = @mkdir -p $(DIST_DIR)
DIST_NAME = $(DIST_DIR).tar.gz

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: install run

install:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TEMP_DIR)
	cd $(TEMP_DIR) && cmake ../3DViewerFront/. -B . -DCMAKE_BUILD_TYPE=Debug . && $(QUIET) cmake --build .
	cp -R $(TEMP_DIR)/$(BUILD_FILE_TEMP) $(BUILD_DIR)/$(BUILD_FILE)
	rm -rf temp

uninstall:
	rm -rf $(BUILD_DIR)/$(BUILD_FILE)

tests: 
	mkdir -p $(TEMP_DIR)
	cd $(TEMP_DIR) && cmake ../test/. -B . -DCMAKE_BUILD_TYPE=Debug . && $(QUIET) cmake --build .
	cp -R $(TEMP_DIR)/$(TEST_FILE) $(BUILD_DIR)/$(TEST_FILE)
	rm -rf temp
	$(BUILD_DIR)/$(TEST_FILE)

html: 
	if [ ! -d $(HTML_DIR)/html ]; then doxygen $(HTML_DIR)/Doxyfile; fi
	open $(HTML_DIR)/html/index.html

dist:
	$(DIST)
	cp -r Makefile ./3DViewerFront ./3DViewerBack ./docs $(DIST_DIR)
	tar -cvzf $(DIST_NAME) $(DIST_DIR)
	rm -rf $(DIST_DIR)

run: 
	$(BUILD_DIR)/$(BUILD_FILE)

debug:
	gdb $(BUILD_DIR)/$(BUILD_FILE)

debug_test:
	gdb $(BUILD_DIR)/$(TEST_FILE)

clean:
	rm -rf *$(_OBJ) *$(_LIB) $(BUILD_DIR)/$(BUILD_FILE) $(EXECUT) $(TEMP_DIR) Settings.ini $(BUILD_DIR)/$(TEST_FILE)