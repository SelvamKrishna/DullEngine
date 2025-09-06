PREMAKE_EXE := ./vendor/premake5.exe
PREMAKE_CC  := gmake
BUILD_DIR   := build
JOBS        := -j8

.PHONY: all clean test final release debug

all: debug

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

test: debug
	$(BUILD_DIR)/debug/application.exe

final: release
	$(BUILD_DIR)/release/application.exe

RELEASE_DIR := $(BUILD_DIR)/release

release: _premake
	@if not exist "$(RELEASE_DIR)" mkdir "$(RELEASE_DIR)"
	@if not exist "$(RELEASE_DIR)/obj" mkdir "$(RELEASE_DIR)/obj"
	$(MAKE) -C $(BUILD_DIR) config=release $(JOBS)

DEBUG_DIR := $(BUILD_DIR)/debug

debug: _premake
	@if not exist "$(DEBUG_DIR)" mkdir "$(DEBUG_DIR)"
	@if not exist "$(DEBUG_DIR)/obj" mkdir "$(DEBUG_DIR)/obj"
	$(MAKE) -C $(BUILD_DIR) config=debug $(JOBS)

_premake: premake5.lua
	$(PREMAKE_EXE) $(PREMAKE_CC) --file=premake5.lua