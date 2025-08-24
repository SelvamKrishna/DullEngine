#include "scene_system.hpp"

#include <cstddef>
#include <mutex>

SceneSystem::~SceneSystem() {
	for (auto& scene : _scene_buffer) {
		if (scene == nullptr) continue;
		scene->clear();
		scene.reset();
	}
}

void SceneSystem::addScene(GameInfo::SceneID scene_id, std::unique_ptr<Scene> new_scene) {
	std::lock_guard<std::mutex> lock(_mutex);

	if (new_scene == nullptr) {
		ErrorCtx("Add scene") .failFallback("Null scene provided");
		return;
	}

	auto& scene = _scene_buffer.at(static_cast<size_t>(scene_id));
	scene.reset();
	scene = std::move(new_scene);

	#ifdef DULL_DBG_SCENES
	DULL_INFO("[SCENE SYSTEM] Scene added with ID '{}'", (size_t)scene_id);
	#endif
}

void SceneSystem::removeScene(GameInfo::SceneID scene_id) {
	std::lock_guard<std::mutex> lock(_mutex);

	auto& scene = _scene_buffer.at(static_cast<size_t>(scene_id));
	if (scene == nullptr) {
		ErrorCtx("Remove scene").failFallback("Trying to remove null scene");
		return;
	}

	scene->clear();
	scene.reset();

	#ifdef DULL_DBG_SCENES
	DULL_INFO("[SCENE SYSTEM] Scene removed with ID '{}'", (size_t)scene_id);
	#endif
}
