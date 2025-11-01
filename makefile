# --- Detect OS ---
ifeq ($(OS),Windows_NT)
    SHELL := cmd
    PREMAKE_EXE := vendor/premake5.exe
    RM := if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    EXE := .exe
else
    SHELL := bash
    PREMAKE_EXE := ./vendor/premake5
    RM := rm -rf $(BUILD_DIR)
    MKDIR = mkdir -p $(1)
    EXE :=
endif

PREMAKE_CC  := gmake
BUILD_DIR   := build
JOBS        := -j8

# --- Premake generation ---
_premake: premake5.lua
	@$(PREMAKE_EXE) $(PREMAKE_CC) --file=premake5.lua

.PHONY: all clean debug release test final help

all: help

clean:
	@echo Cleaning build directory...
	@$(RM)

# --- Debug target ---
debug: _premake
ifeq ($(OS),Windows_NT)
	@if not exist "$(BUILD_DIR)\debug\obj" mkdir "$(BUILD_DIR)\debug\obj"
else
	@mkdir -p "$(BUILD_DIR)/debug/obj"
endif
	@$(MAKE) -C $(BUILD_DIR) config=debug $(JOBS)

# --- Release target ---
release: _premake
ifeq ($(OS),Windows_NT)
	@if not exist "$(BUILD_DIR)\release\obj" mkdir "$(BUILD_DIR)\release\obj"
else
	@mkdir -p "$(BUILD_DIR)/release/obj"
endif
	@$(MAKE) -C $(BUILD_DIR) config=release $(JOBS)

test: debug
	@$(BUILD_DIR)/debug/application$(EXE)

final: release
	@$(BUILD_DIR)/release/application$(EXE)

help:
	@echo "Available targets:"
	@echo "  clean   - Remove build artifacts"
	@echo "  debug   - Build in debug mode"
	@echo "  release - Build in release mode"
	@echo "  test    - Build in debug mode and run application"
	@echo "  final   - Build in release mode and run application"
