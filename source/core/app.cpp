#include "app.hpp"

#include "../../vendor/raylib.h"
#include "constants.hpp"

#include <memory>

App::App() {
    if (_is_running) [[unlikely]] {
        ErrorCtx("App initialization").failExit("Run flag set to true");
    }

    InitWindow(GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT, TITLE);
    SetExitKey(KEY_NULL);
    _is_running = true;
    AudioSystem::_init();
}

App::~App() { CloseWindow(); }

void App::_processNull() noexcept { RenderSystem::_drawNull(); }

void App::_processFixed() {
    _accumulator += _time_sys.deltaTime();

    while (_accumulator >= TimeSystem::FIXED_DELTA_TIME) [[unlikely]] {
        _scene_sys._fixedUpdateCurrentScene();
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
    ErrorCtx err("App mainloop");

    if (!_is_running) [[unlikely]] {
        err.failExit("Run flag set to false");
    }

    if (_render_sys == nullptr) {
        _render_sys = std::make_unique<RenderSystem>();
    }

    _scene_sys._initCurrentScene();
    _render_sys->_init();

    while (_is_running) [[likely]] {
        try {
            if (WindowShouldClose()) [[unlikely]] {
                _is_running = false;
                break;
            }

            _time_sys._updateInfo(GetFrameTime());
            _time_sys.isPaused() ? _processNull() : _process();

        } catch (const std::exception &RUNTIME_ERR) {
            _is_running = false;
            ErrorCtx("Runtime").failExit(RUNTIME_ERR.what());
        }
    }
}