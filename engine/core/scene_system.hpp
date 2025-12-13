#pragma once

#include "engine/core/layer_buffer.hpp"
#include "engine/core/scene.hpp"

namespace dull::core {

class SceneSystem final {
    friend class App;

private:
    LayerBuffer _layer_buffer;

    explicit SceneSystem() = default;
    ~SceneSystem() = default;

    void _activate();
    void _process();
    void _fixedProcess();

public:
    Scene current_scene;

    [[nodiscard]]
    LayerBuffer& getLayerBuffer() noexcept { return _layer_buffer; }
};

} // namespace dull::core
