#pragma once

#include "engine/process/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

// =======================
// Builder patter for Scene
// =======================
class SceneBuilder {
private:
    std::unique_ptr<process::Scene> _scene;

public:
    static constexpr size_t DEFAULT_CAPACITY { 16 };

    explicit SceneBuilder(std::string layer_name, size_t reserve = DEFAULT_CAPACITY);

    // Adds `Layer` to `Scene`
    SceneBuilder& addLayer(std::string_view layer_name, size_t idx = UINT64_MAX, bool active = true);

    [[nodiscard]]
    std::unique_ptr<process::Scene> build() noexcept;

    // Directly pushes `Scene` into the static `SceneBuffer` within `World`
    void pushToBuffer() noexcept;
};

} // namespace dull::misc
