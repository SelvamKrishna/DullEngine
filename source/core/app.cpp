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
    if (_is_running) {
        DULL_WARN("App::init() called multiple times (window already initialized)");
        return;
    }

    InitWindow(window_width, window_height, title.c_str());
    SetExitKey(KEY_NULL);
    _is_running = true;
    AudioSystem::_init();
}

void App::run() {
    if (!_is_running) {
        DULL_WARN("App::run() called without prior initialization (call init() first)");
        return;
    }

    if (!_render_sys) {
        _render_sys = std::make_unique<RenderSystem>();
    }

    if (!_current_scene) {
        DULL_WARN("Trying to run application without setting initializing current scene");
        return;
    }

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
            DULL_WARN("Runtime error: %s", RUNTIME_ERR.what());
        }
    }
}