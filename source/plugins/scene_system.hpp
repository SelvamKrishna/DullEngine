#pragma once

#include "../core/constants.hpp"
#include "../core/scene.hpp"

#include <array>
#include <cstddef>
#include <memory>
#include <mutex>

class SceneSystem {
    friend class App;

private:
    mutable std::mutex _mutex;
    std::array<std::unique_ptr<Scene>, GameInfo::TOTAL_SCENE_COUNT> _scene_buffer;
    size_t _current_scene_id = 0;

    explicit SceneSystem() = default;

public:
    ~SceneSystem();

    SceneSystem(const SceneSystem &) = delete;
    SceneSystem(SceneSystem &&) = delete;
    SceneSystem &operator=(const SceneSystem &) = delete;
    SceneSystem &operator=(SceneSystem &&) = delete;

    void setCurrent(size_t new_scene_id) noexcept {
        std::lock_guard<std::mutex> lock(_mutex);
        ErrorCtx err("Set current scene");

        if (new_scene_id >= _scene_buffer.size()) {
            err.failFallback("Scene index out of range");
            return;
        }

        _current_scene_id = new_scene_id;

        if (_scene_buffer.at(_current_scene_id) == nullptr) {
            err.failExit("Current scene is unimplemented");
        }
    }

    void ChangeScene(size_t new_scene_id) noexcept {
        setCurrent(new_scene_id);
        _scene_buffer.at(_current_scene_id)->_init();
    }

    [[nodiscard]] Scene &currentScene() const {
        if (const auto &current_scene = _scene_buffer.at(_current_scene_id)) {
            return *current_scene;
        }

        ErrorCtx("Get current scene").failExit("Current scene is unimplemented");
    }

    void addScene(size_t scene_id, std::unique_ptr<Scene> new_scene);
    void removeScene(size_t scene_id);
};