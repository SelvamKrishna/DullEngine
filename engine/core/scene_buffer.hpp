#pragma once

#include "engine/config.hpp"
#include "engine/core/scene.hpp"

#include <memory>

namespace dull::core {

class SceneBuffer final {
    friend class SceneSystem;

private:
    std::vector<std::unique_ptr<Scene>> _scenes;

    constexpr SceneBuffer(SceneBuffer&&)                 noexcept = delete;
    constexpr SceneBuffer(const SceneBuffer&)            noexcept = delete;
    constexpr SceneBuffer& operator=(SceneBuffer&&)      noexcept = delete;
    constexpr SceneBuffer& operator=(const SceneBuffer&) noexcept = delete;

    SceneBuffer();
    ~SceneBuffer() = default;

public:
    void loadScene(config::SceneID scene_id, std::unique_ptr<Scene> scene);

    [[nodiscard]]
    std::unique_ptr<Scene>& getScene(config::SceneID scene_id) noexcept;

    [[nodiscard]]
    size_t sceneCount() const noexcept { return _scenes.size(); }

    void logStats() const noexcept;
};

} // namespace dull::core
