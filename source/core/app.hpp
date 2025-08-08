#pragma once

#include "../plugins/audio_system.hpp"
#include "../plugins/render_system.hpp"
#include "../plugins/scene_system.hpp"
#include "../plugins/signal_system.hpp"
#include "../plugins/time_system.hpp"
#include "../utils/debug.hpp"

#include "scene.hpp"

#include <memory>
#include <string>
#include <type_traits>

class App {
private:
    float _accumulator = 0.0F;
    bool _is_running = false;

    SceneSystem _scene_sys;
    TimeSystem _time_sys;
    AudioSystem _audio_sys;
    SignalSystem _signal_sys;
    std::unique_ptr<RenderSystem> _render_sys;

    explicit App() = default;
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

    void init();
    void run();
    constexpr void quit() noexcept { _is_running = false; }

    [[nodiscard]] constexpr bool isRunning() const noexcept { return _is_running; }

    [[nodiscard]] constexpr SceneSystem &sceneSystem() noexcept { return _scene_sys; }
    [[nodiscard]] constexpr TimeSystem &timeSystem() noexcept { return _time_sys; }
    [[nodiscard]] constexpr AudioSystem &audioSystem() noexcept { return _audio_sys; }
    [[nodiscard]] constexpr SignalSystem &signalSystem() noexcept { return _signal_sys; }

    void setRenderSystem(std::unique_ptr<RenderSystem> render_sys) noexcept {
        _render_sys = std::move(render_sys);
    }

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
};

#define SCENE_SYS App::instance().sceneSystem()
#define TIME_SYS App::instance().timeSystem()
#define AUDIO_SYS App::instance().audioSystem()
#define RENDER_SYS() App::instance().renderSystem()
#define RENDER_SYS_AS(Type) App::instance().renderSystem<Type>()
#define SIGNAL_SYS App::instance().signalSystem()

#define CURRENT_SCENE SCENE_SYS.currentScene()