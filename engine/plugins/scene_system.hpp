#pragma once

#include "engine/core/scene.hpp"

#include <array>
#include <cstddef>
#include <memory>
#include <mutex>

/// Collection of scenes;
/// Provides API for scene handling;
class SceneSystem {
	friend class App;

private:
	mutable std::mutex _mutex;
	std::array<std::unique_ptr<Scene>, GameInfo::TOTAL_SCENE_COUNT> _scene_buffer;
	GameInfo::SceneID _current_scene_id;

	explicit SceneSystem() = default;

	void _initCurrentScene() const {
		currentScene()._init();

		#ifdef DULL_DBG_SCENES
		DULL_INFO("[SCENE SYSTEM] Current scene SceneID '{}' initialized", (size_t)_current_scene_id);
		#endif
	}

	void _updateCurrentScene() const { currentScene()._update(); }
	void _fixedUpdateCurrentScene() const { currentScene()._fixedUpdate(); }

public:
	~SceneSystem();

	SceneSystem(const SceneSystem&) = delete;
	SceneSystem(SceneSystem&&) = delete;
	SceneSystem& operator=(const SceneSystem&) = delete;
	SceneSystem& operator=(SceneSystem&&) = delete;

	void setCurrent(GameInfo::SceneID new_scene_id) noexcept {
		// !This method shouls only be called once
		std::lock_guard<std::mutex> lock(_mutex);
		_current_scene_id = new_scene_id;

		if (_scene_buffer.at(static_cast<size_t>(_current_scene_id)) == nullptr) {
			ErrorCtx{"Set current scene"}
				.failExit("Current scene is unimplemented");
		}

		#ifdef DULL_DBG_SCENES
		DULL_INFO("[SCENE SYSTEM] Current scene set to SceneID '{}'", (size_t)_current_scene_id);
		#endif
	}

	void changeScene(GameInfo::SceneID new_scene_id) noexcept {
		setCurrent(new_scene_id);
		_initCurrentScene();
	}

	[[nodiscard]] Scene& currentScene() const {
		const std::unique_ptr<Scene>& CURRENT_SCENE = _scene_buffer.at(static_cast<size_t>(_current_scene_id));

		if (CURRENT_SCENE == nullptr) {
			ErrorCtx{"Get current scene"}
				.failExit("Current scene is unimplemented");
		}

		return *CURRENT_SCENE;
	}

	void addScene(GameInfo::SceneID scene_id, std::unique_ptr<Scene> new_scene);
	void removeScene(GameInfo::SceneID scene_id);
};