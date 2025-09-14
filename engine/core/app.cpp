#include "app/constants.hpp"

#include "engine/core/app.hpp"
#include "engine/core/constants.hpp"
#include "engine/plugins/physics_system.hpp"
#include "engine/utils/debug.hpp"

#include "vendor/raylib.h"

#include <memory>
#include <string>

/// TODO: Implement window sizing support
/// TODO: Implement window fullscreen support
App::App() {
	const std::string TITLE { 
		#ifdef DULL_MODE_DEBUG
		std::string("Dull Engine ") +
		std::to_string(EngineInfo::VERSION_MAJOR) + "." +
		std::to_string(EngineInfo::VERSION_MINOR) + " - " +
		#endif
		GameInfo::TITLE
		#ifdef DULL_MODE_DEBUG
		+ " " +
		std::to_string(GameInfo::VERSION_MAJOR) + "." +
		std::to_string(GameInfo::VERSION_MINOR)
		#endif
	};

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
		_scene_sys._fixedUpdateCurrentScene();
		_physics_sys->_update(); // to be handled in fixed interval
		_accumulator -= TimeSystem::FIXED_DELTA_TIME;
	}
}

void App::_process() {
	_processFixed();
	_scene_sys._updateCurrentScene();
	_render_sys->_update();
	_audio_sys._update();
}

void App::run() {
	ErrorCtx err{"Run application"};

	if (_render_sys == nullptr) {
		_render_sys = std::make_unique<RenderSystem>();
		DULL_WARN("[APP] Render system not set. implementing default variant.");
	}

	if (_physics_sys == nullptr) {
		_physics_sys = std::make_unique<PhysicsSystem>();
		DULL_WARN("[APP] physics system not set. implementing default variant.");
	}

	_scene_sys._initCurrentScene();
	_render_sys->_init();
	_physics_sys->_init();

	while (!WindowShouldClose()) [[likely]] {
		try {
			_time_sys._updateInfo(GetFrameTime());
			_time_sys.isPaused() ? _processNull() : _process();

		} catch (const std::exception& RUNTIME_ERR) {
			err.failExit(RUNTIME_ERR.what());

		}
	}
}