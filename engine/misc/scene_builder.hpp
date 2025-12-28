#pragma once

#include "engine/process/layer.hpp"
#include "engine/process/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

class SceneBuilder {
private:
    std::unique_ptr<process::Scene> _scene;

public:
    explicit SceneBuilder(std::string scene_name);

    SceneBuilder& reserve(size_t capacity) noexcept;
    SceneBuilder& addLayer(std::string_view layer_name, size_t idx = UINT64_MAX, bool active = true);

    [[nodiscard]]
    std::unique_ptr<process::Scene> build() noexcept;
    void pushToBuffer() noexcept;
};

} // namespace dull::misc
