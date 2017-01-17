#Build directories
BIN_DIR=./build
OBJ_DIR=./obj

# Source directories
HEADER_DIR=./include
SRC_DIR=./src

# Test directories
TESTSRC_DIR=$(SRC_DIR)/test
TESTBIN_DIR=$(BIN_DIR)/test

# Point to your gtest install
GTEST_DIR=./googletest

# Compile flags
CPP=g++
CPPFLAGS=-std=c++11 -g -I$(HEADER_DIR)
GTESTCFLAGS=-isystem $(GTEST_DIR)/include/ -pthread
GTESTLDFLAGS=-L $(GTEST_DIR) -lgtest_main -lgtest

# executables
OBJS=$(OBJ_DIR)/findroute.o \
     $(OBJ_DIR)/main.o
TESTS=$(TESTBIN_DIR)/findroute
APP=$(BIN_DIR)/app

all: directories $(OBJS) app

app: $(APP)

tests: $(OBJS) $(TESTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

$(TESTBIN_DIR)/%: $(TESTSRC_DIR)/%_test.cpp $(OBJ_DIR)/%.o
	$(CPP) $(CPPFLAGS) $(INCLUDE) $(GTESTCFLAGS) $(GTESTLDFLAGS) $^ -o $@
	$@

$(APP): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDE) $(OBJS) -o $@
	
.PHONY: directories
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(TESTBIN_DIR)

.PHONY: clean_directories
clean_directories:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(TESTBIN_DIR)

.PHONY: clean
clean: clean_directories directories
