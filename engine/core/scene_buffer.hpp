#pragma once

#include "engine/config.hpp"
#include "engine/core/scene.hpp"

#include <memory>
#include <array>

namespace dull::core {

// =======================
// Collection of all Scene related data
// =======================
class SceneBuffer final {
    friend class SceneSystem;

private:
    // Fixed size array size calculated from SceneID enum in dull::config
    std::array<std::unique_ptr<Scene>, static_cast<size_t>(config::SceneID::_COUNT)> _scenes;

    constexpr SceneBuffer(SceneBuffer&&)                 noexcept = delete;
    constexpr SceneBuffer(const SceneBuffer&)            noexcept = delete;
    constexpr SceneBuffer& operator=(SceneBuffer&&)      noexcept = delete;
    constexpr SceneBuffer& operator=(const SceneBuffer&) noexcept = delete;

    SceneBuffer();
    ~SceneBuffer() = default;

public:
    // Loads scene into buffer
    void loadScene(config::SceneID scene_id, std::unique_ptr<Scene> scene);

    // Get access to scene using its unique ID
    [[nodiscard]]
    std::unique_ptr<Scene>& getScene(config::SceneID scene_id) noexcept;

    [[nodiscard]]
    size_t sceneCount() const noexcept { return _scenes.size(); }

    // DEV: Logs all scenes within buffer
    void logStats() const noexcept;
};

} // namespace dull::core
