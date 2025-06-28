# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Iinclude -Isource -Ivendor

DEBUG_FLAGS := -Wall -Wextra -g -O2
RELEASE_FLAGS := -Wall -Wextra -Werror -O3

LDFLAGS := vendor/libraylib.a -lwinmm -lgdi32 -lopengl32

# Directory structure
SOURCE_DIR := source
TESTS_DIR := tests
BUILD_DIR := build

# Engine source and object files
ENGINE_SRC := $(wildcard $(SOURCE_DIR)/*/*.cpp) $(wildcard $(SOURCE_DIR)/*/*/*.cpp)
ENGINE_OBJ := $(ENGINE_SRC:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/engine/%.o)

# Sandbox/test files
SANDBOX_SRC := $(wildcard $(TESTS_DIR)/*.cpp)
SANDBOX_OBJ := $(SANDBOX_SRC:$(TESTS_DIR)/%.cpp=$(BUILD_DIR)/sandbox/%.o)

# Output targets
ENGINE_LIB := $(BUILD_DIR)/libdullengine.a
SANDBOX_BIN := $(BUILD_DIR)/sandbox.exe

# Default target
all: debug

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(SANDBOX_BIN)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(SANDBOX_BIN)

# Build static engine library
$(ENGINE_LIB): $(ENGINE_OBJ)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	ar rcs $@ $^

# Compile engine sources
$(BUILD_DIR)/engine/%.o: $(SOURCE_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile sandbox/test sources
$(BUILD_DIR)/sandbox/%.o: $(TESTS_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link sandbox binary
$(SANDBOX_BIN): $(SANDBOX_OBJ) $(ENGINE_LIB)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $^ -o $@ $(LDFLAGS)

# Run sandbox
run: debug
	$(SANDBOX_BIN)

# Clean build output
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

.PHONY: all debug release run clean
