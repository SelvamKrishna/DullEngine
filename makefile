# Makefile for building a C++ project with Raylib
CXX := g++
CXXFLAGS := -std=c++20 -Iinclude -Isource -Ivendor

DEBUG_FLAGS := -Wall -Wextra -g -O2 -DDEBUG
RELEASE_FLAGS := -Wall -Wextra -Werror -O3 -DNDEBUG -DDULL_MODE_DEBUG

LDFLAGS := vendor/libraylib.a -lwinmm -lgdi32 -lopengl32

# Directories
SOURCE_DIR := source
APP_DIR := app
BUILD_DIR := build

# Compile engine sources
ENGINE_SRC := $(wildcard $(SOURCE_DIR)/*/*.cpp) $(wildcard $(SOURCE_DIR)/*/*/*.cpp)
ENGINE_OBJ := $(ENGINE_SRC:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/$(SOURCE_DIR)/%.o)

# Compile project sources
PROJECT_SRC := $(wildcard $(APP_DIR)/*.cpp)
PROJECT_OBJ := $(PROJECT_SRC:$(APP_DIR)/%.cpp=$(BUILD_DIR)/$(APP_DIR)/%.o)

# Output targets
ENGINE_LIB := $(BUILD_DIR)/libdullengine.a
PROJECT_BIN := $(BUILD_DIR)/application.exe

# Default target
all: debug

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(PROJECT_BIN)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(PROJECT_BIN)

# Build static engine library
$(ENGINE_LIB): $(ENGINE_OBJ)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	ar rcs $@ $^

# Compile engine sources
$(BUILD_DIR)/$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile project sources
$(BUILD_DIR)/$(APP_DIR)/%.o: $(APP_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link project binary
$(PROJECT_BIN): $(PROJECT_OBJ) $(ENGINE_LIB)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $^ -o $@ $(LDFLAGS)

# Run project
run: debug
	$(PROJECT_BIN)

# Clean build output
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

.PHONY: all debug release run clean
