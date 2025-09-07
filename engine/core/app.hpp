#pragma once

#include "engine/core/scene.hpp"
#include "engine/plugins/audio_system.hpp"
#include "engine/plugins/global_system.hpp"
#include "engine/plugins/render_system.hpp"
#include "engine/plugins/scene_system.hpp"
#include "engine/plugins/signal_system.hpp"
#include "engine/plugins/time_system.hpp"
#include "engine/utils/debug.hpp"

#include <memory>
#include <string>
#include <type_traits>

/// Main handle for all nodes and systems;
class App {
private:
	float _accumulator = 0.0F;

	SceneSystem _scene_sys;
	TimeSystem _time_sys;
	AudioSystem _audio_sys;
	SignalSystem _signal_sys;
	std::unique_ptr<RenderSystem> _render_sys; /// (MODIFIABLE)
	std::unique_ptr<GlobalSystem> _global_sys; /// (MODIFIABLE)

	explicit App();
	~App();

	static void _processNull() noexcept;
	void _processFixed();
	void _process();

public:
	App(App&&) = delete;
	App& operator=(App&&) = delete;
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	static App& instance() noexcept {
		static App instance;
		return instance;
	}

	void run();

	[[nodiscard]] constexpr SceneSystem& sceneSystem() noexcept { return _scene_sys; }
	[[nodiscard]] constexpr TimeSystem& timeSystem() noexcept { return _time_sys; }
	[[nodiscard]] constexpr AudioSystem& audioSystem() noexcept { return _audio_sys; }
	[[nodiscard]] constexpr SignalSystem& signalSystem() noexcept { return _signal_sys; }

	void setRenderSystem(std::unique_ptr<RenderSystem> render_sys) noexcept {
		bool overwrite = _render_sys != nullptr;
		_render_sys = std::move(render_sys);

		// Re-initialize render system if changed while application running
		if (overwrite) _render_sys->_init();
	}

	[[nodiscard]] RenderSystem& renderSystem() noexcept {
		if (_render_sys == nullptr) 
			_TODO("Set render system before accessing; APP.setRenderSystem(unique_ptr to render system)");
		return *_render_sys;
	}

	template <typename RenderSystemT>
		requires std::is_base_of_v<RenderSystem, RenderSystemT>
	[[nodiscard]] RenderSystemT& renderSystem() {
		if (auto* casted_sys = dynamic_cast<RenderSystemT*>(_render_sys.get()))
			return *casted_sys;
		ErrorCtx{"Get render system"}.failExit("Bad cast");
	}

	void setGlobalSystem(std::unique_ptr<GlobalSystem> global_sys) noexcept {
		if (_global_sys != nullptr) {
			ErrorCtx{"Set global system"}.failFallback("Can't be overwritten");
			return;
		}

		_global_sys = std::move(global_sys);
	}

	[[nodiscard]] GlobalSystem& globalSystem() noexcept {
		if (_global_sys == nullptr)
			_TODO("Set global system before accessing; APP.setGlobalSystem(unique_ptr to global system)");
		return *_global_sys;
	}

	template <typename GlobalSystemT>
		requires std::is_base_of_v<GlobalSystem, GlobalSystemT>
	[[nodiscard]] GlobalSystemT& globalSystem() {
		if (auto* casted_sys = dynamic_cast<GlobalSystemT*>(_global_sys.get()))
			return *casted_sys;
		ErrorCtx{"Get global system"}.failExit("Bad cast");
	}
};

#define APP					App::instance()
#define SCENE_SYS			APP.sceneSystem()
#define TIME_SYS			APP.timeSystem()
#define AUDIO_SYS			APP.audioSystem()
#define SIGNAL_SYS			APP.signalSystem()
#define RENDER_SYS			APP.renderSystem()
#define RENDER_SYS_AS(T)	APP.renderSystem<T>()
#define GLOBAL_SYS			APP.globalSystem()
#define GLOBAL_SYS_AS(T)	APP.globalSystem<T>()

#define CURRENT_SCENE		SCENE_SYS.currentScene()
#define D_TIME				TIME_SYS.deltaTime()