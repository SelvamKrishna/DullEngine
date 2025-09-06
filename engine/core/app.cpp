#include "engine/core/app.hpp"
#include "engine/core/constants.hpp"

#include "vendor/raylib.h"

#include <memory>
#include <string>

App::App() {
	const std::string TITLE =
		#ifdef DULL_MODE_DEBUG
		std::string("Dull Engine-") +
		std::to_string(EngineInfo::VERSION_MAJOR) + "." +
		std::to_string(EngineInfo::VERSION_MINOR) + " " +
		#endif
		GameInfo::TITLE;

	InitWindow(GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT, TITLE.c_str());
	SetExitKey(KEY_NULL);

	_is_running = true;
	AudioSystem::_init();
}

App::~App() { CloseWindow(); }

void App::_processNull() noexcept { RenderSystem::_drawNull(); }

void App::_processFixed() {
	_accumulator += _time_sys.deltaTime();

	// Update in fixed frame duration
	while (_accumulator >= TimeSystem::FIXED_DELTA_TIME) [[unlikely]] {
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

	// Implement default variants of system
	if (_render_sys == nullptr) _render_sys = std::make_unique<RenderSystem>();
	if (_global_sys == nullptr) _global_sys = std::make_unique<GlobalSystem>();

	_scene_sys._initCurrentScene();
	_render_sys->_init();
	_global_sys->_init();

	while (_is_running) [[likely]] {
		try {
			if (WindowShouldClose()) [[unlikely]] { _is_running = false; break; }

			_time_sys._updateInfo(GetFrameTime());
			_time_sys.isPaused() ? _processNull() : _process();

		} catch (const std::exception& RUNTIME_ERR) {
			_is_running = false;
			ErrorCtx{"Runtime"}.failExit(RUNTIME_ERR.what());
		}
	}
}