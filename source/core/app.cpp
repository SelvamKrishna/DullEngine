#include "app.hpp"

#include "../../vendor/raylib.h"

#include <memory>

App::~App() { CloseWindow(); }

void App::_processNull() { RenderSystem::_drawNull(); }

void App::_processFixed() {
    _accumulator += _time_sys.deltaTime();

    while (_accumulator >= TimeSystem::FIXED_DELTA_TIME) [[unlikely]] {
        _current_scene->_fixedUpdate();
        _accumulator -= TimeSystem::FIXED_DELTA_TIME;
    }
}

void App::_process() {
    _processFixed();

    _current_scene->_update();
    _render_sys->_update();
    _audio_sys._update();
}

void App::init(int window_width, int window_height, const std::string &title) {
    if (_is_running) [[unlikely]] {
        ErrorCtx("App initialization").failExit("Run flag set to true");
    }

    InitWindow(window_width, window_height, title.c_str());
    SetExitKey(KEY_NULL);
    _is_running = true;
    AudioSystem::_init();
}

void App::run() {
    ErrorCtx err("App mainloop");

    if (!_is_running) {
        err.failExit("Run flag set to false");
    }

    if (!_current_scene) {
        err.failExit("Current scene not yet set");
    }

    if (!_render_sys) {
        _render_sys = std::make_unique<RenderSystem>();
    }

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