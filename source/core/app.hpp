#pragma once

#include "../plugins/audio_system.hpp"
#include "../plugins/render_system.hpp"
#include "../plugins/signal_system.hpp"
#include "../plugins/time_system.hpp"

#include "../utils/debug.hpp"

#include "scene.hpp"

#include <memory>
#include <string>
#include <type_traits>

class App {
private:
    std::unique_ptr<Scene> _current_scene;
    float _accumulator = 0.0F;
    bool _is_running = false;

    TimeSystem _time_sys;
    AudioSystem _audio_sys;
    std::unique_ptr<RenderSystem> _render_sys;
    SignalSystem _signal_sys;

    App() = default;
    ~App();

    inline static void _processNull();
    inline void _processFixed();
    inline void _process();

public:
    App(App &&) = delete;
    App &operator=(App &&) = delete;
    App(const App &) = delete;
    App &operator=(const App &) = delete;

    static App &instance() noexcept {
        static App instance;
        return instance;
    }

    void init(int window_width, int window_height, const std::string &title);
    void run();
    constexpr void quit() noexcept { _is_running = false; }

    void setCurrentScene(std::unique_ptr<Scene> scene) noexcept { _current_scene = std::move(scene); }

    void setRenderSystem(std::unique_ptr<RenderSystem> render_sys) noexcept {
        _render_sys = std::move(render_sys);
    }

    [[nodiscard]] Scene &currentScene() const {
        if (_current_scene) {
            return *_current_scene;
        }

        ErrorCtx("Get current scene").failExit("Scene not yet set");
    }

    [[nodiscard]] constexpr bool isRunning() const noexcept { return _is_running; }

    [[nodiscard]] constexpr TimeSystem &timeSystem() noexcept { return _time_sys; }
    [[nodiscard]] constexpr AudioSystem &audioSystem() noexcept { return _audio_sys; }

    [[nodiscard]] RenderSystem &renderSystem() noexcept {
        if (_render_sys == nullptr) {
            _render_sys = std::make_unique<RenderSystem>();
        }

        return *_render_sys;
    }

    template <typename RenderSystemT>
        requires std::is_base_of_v<RenderSystem, RenderSystemT>
    [[nodiscard]] constexpr RenderSystemT &renderSystem() const {
        if (auto *casted_sys = dynamic_cast<RenderSystemT *>(_render_sys.get())) {
            return *casted_sys;
        }

        ErrorCtx("Get render system").failExit("Bad cast");
    }

    [[nodiscard]] constexpr SignalSystem &signalSystem() noexcept { return _signal_sys; }
};

#define CURRENT_SCENE App::instance().currentScene()
#define TIME_SYS App::instance().timeSystem()
#define AUDIO_SYS App::instance().audioSystem()
#define RENDER_SYS() App::instance().renderSystem()
#define RENDER_SYS_AS(Type) App::instance().renderSystem<Type>()
#define SIGNAL_SYS App::instance().signalSystem()