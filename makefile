PREMAKE_EXE := ./vendor/premake5.exe
PREMAKE_CC  := gmake
BUILD_DIR   := build

.PHONY: all clean test final release debug

all: _premake

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

test: debug
	$(BUILD_DIR)/debug/application.exe

final: release
	$(BUILD_DIR)/release/application.exe

release: _premake
	$(MAKE) -C $(BUILD_DIR) config=release

debug: _premake
	$(MAKE) -C $(BUILD_DIR) config=debug
	
_premake: premake5.lua
	$(PREMAKE_EXE) $(PREMAKE_CC) --file=premake5.lua