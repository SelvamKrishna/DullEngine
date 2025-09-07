#include "engine/core/app.hpp"
#include "engine/core/constants.hpp"

#include "engine/utils/debug.hpp"
#include "vendor/raylib.h"

#include <memory>
#include <string>

/// TODO: Implement window sizing support
/// TODO: Implement window fullscreen support
App::App() {
	const std::string TITLE =
		#ifdef DULL_MODE_DEBUG
		std::string("Dull Engine ") +
		std::to_string(EngineInfo::VERSION_MAJOR) + "." +
		std::to_string(EngineInfo::VERSION_MINOR) + " - " +
		#endif
		GameInfo::TITLE + " " +
		std::to_string(GameInfo::VERSION_MAJOR) + "." +
		std::to_string(GameInfo::VERSION_MINOR) + " ";

	InitWindow(GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT, TITLE.c_str());
	SetExitKey(KEY_NULL);

	AudioSystem::_init();
}

App::~App() { CloseWindow(); }

void App::_processNull() noexcept { RenderSystem::_drawNull(); }

void App::_processFixed() {
	_accumulator += _time_sys.deltaTime();

	// Update in fixed frame duration
	while (_accumulator >= TimeSystem::FIXED_DELTA_TIME) {
		_global_sys->_fixedUpdate();
		_scene_sys._fixedUpdateCurrentScene();
		_accumulator -= TimeSystem::FIXED_DELTA_TIME;
	}
}

void App::_process() {
	_processFixed();
	_global_sys->_update();
	_scene_sys._updateCurrentScene();
	_render_sys->_update();
	_audio_sys._update();
}

void App::run() {
	ErrorCtx err{"App mainloop"};

	if (_render_sys == nullptr) {
		_render_sys = std::make_unique<RenderSystem>();
		DULL_WARN("[APP] Render system not set. implementing default variant.");
	}

	if (_global_sys == nullptr) {
		_global_sys = std::make_unique<GlobalSystem>();
		DULL_WARN("[APP] Global system not set. implementing default variant.");
	}

	_scene_sys._initCurrentScene();
	_render_sys->_init();
	_global_sys->_init();

	while (!WindowShouldClose()) [[likely]] {
		try {
			_time_sys._updateInfo(GetFrameTime());
			_time_sys.isPaused() ? _processNull() : _process();

		} catch (const std::exception& RUNTIME_ERR) {
			ErrorCtx{"Runtime"}.failExit(RUNTIME_ERR.what());
			break;
		}
	}
}