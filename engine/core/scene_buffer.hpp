#pragma once

#include "engine/core/scene.hpp"

#include <memory>
#include <vector>
#include <string_view>

namespace dull::core {

// =======================
// Collection of all Scene related data
// =======================
class SceneBuffer final {
    friend class SceneSystem;

private:
    std::vector<std::unique_ptr<Scene>> _scenes;

    using SceneIt = std::vector<std::unique_ptr<Scene>>::iterator;

    constexpr SceneBuffer(SceneBuffer&&)                 noexcept = delete;
    constexpr SceneBuffer(const SceneBuffer&)            noexcept = delete;
    constexpr SceneBuffer& operator=(SceneBuffer&&)      noexcept = delete;
    constexpr SceneBuffer& operator=(const SceneBuffer&) noexcept = delete;

    explicit SceneBuffer() = default;
    ~SceneBuffer() = default;

    SceneIt _findScene(std::string_view scene_name) noexcept;

public:
    // Loads scene into buffer
    void loadScene(std::unique_ptr<Scene> scene);

    // Get access to scene using its unique ID
    [[nodiscard]]
    std::unique_ptr<Scene>& getScene(std::string_view scene_name) noexcept;

    [[nodiscard]]
    bool hasScene(std::string_view& scene_name) noexcept;

    [[nodiscard]]
    size_t sceneCount() noexcept { return _scenes.size(); }

    // DEV: Logs all scenes within buffer
    void logStats() const noexcept;
};

} // namespace dull::core
