#include "scene_system.hpp"
#include <cstddef>
#include <mutex>

SceneSystem::~SceneSystem() {
    for (auto &scene : _scene_buffer) {
        if (scene != nullptr) {
            scene->clear();
            scene.reset();
        }
    }
}

void SceneSystem::addScene(size_t scene_id, std::unique_ptr<Scene> new_scene) {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err("Add scene");

    if (scene_id >= _scene_buffer.size()) {
        err.failFallback("Scene ID out of range");
        return;
    }

    if (new_scene == nullptr) {
        err.failFallback("Null scene provided");
        return;
    }

    _scene_buffer[scene_id].reset();
    _scene_buffer[scene_id] = std::move(new_scene);
}

void SceneSystem::removeScene(size_t scene_id) {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err("Remove scene");

    if (scene_id >= _scene_buffer.size()) {
        err.failFallback("Scene ID out of range");
        return;
    }

    if (auto &scene = _scene_buffer.at(scene_id)) {
        scene->clear();
        scene.reset();
    } else {
        err.failFallback("Trying to remove null scene");
    }
}
