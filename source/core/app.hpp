#pragma once

#include "../plugins/audio_system.hpp"
#include "../plugins/render_system.hpp"
#include "../plugins/time_system.hpp"

#include "../utils/debug.hpp"

#include "scene.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

class App {
private:
    std::unique_ptr<Scene> _current_scene;
    float _accumulator = 0.0F;
    bool _is_running = false;

    TimeSystem &_time_sys = TimeSystem::instance();
    AudioSystem &_audio_sys = AudioSystem::instance();
    std::unique_ptr<RenderSystem> _render_sys;

    App() = default;
    ~App();

    inline static void _processNull();
    inline void _processFixed();
    inline void _process();

public:
    static App &instance() {
        static App instance;
        return instance;
    }

    App(const App &) = delete;
    App &operator=(const App &) = delete;

    void init(int window_width, int window_height, const std::string &title);
    void run();
    void quit() noexcept { _is_running = false; }

    void setCurrentScene(std::unique_ptr<Scene> scene) { _current_scene = std::move(scene); }
    void setRenderSystem(std::unique_ptr<RenderSystem> render_sys) { _render_sys = std::move(render_sys); }

    Scene &currentScene() {
        if (_current_scene) {
            return *_current_scene;
        }

        DULL_ERROR("Failed to get current scene: Scene not yet set.");
        throw std::runtime_error(TRACE_MSG("Failed to get current scene: Scene not yet set."));
    }

    [[nodiscard]] bool isRunning() const noexcept { return _is_running; }

    TimeSystem &timeSystem() noexcept { return _time_sys; }
    AudioSystem &audioSystem() noexcept { return _audio_sys; }
    RenderSystem &renderSystem() {
        if (!_render_sys) {
            _render_sys = std::make_unique<RenderSystem>();
        }

        return *_render_sys;
    }

    template <typename RenderSystemT>
        requires std::is_base_of_v<RenderSystem, RenderSystemT>
    RenderSystemT &renderSystem() {
        if (auto *casted_sys = dynamic_cast<RenderSystemT *>(_render_sys.get())) {
            return *casted_sys;
        }

        DULL_WARN("Unable to cast render system to given type");
        throw std::bad_cast();
    }
};