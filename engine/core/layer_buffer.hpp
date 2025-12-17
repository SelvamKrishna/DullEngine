#pragma once

#include "engine/core/layer.hpp"
#include "engine/misc/string_view_hashing.hpp"

#include <unordered_map>
#include <string_view>
#include <memory>

namespace dull::core {

// =======================
// List of all Layers
// =======================
class LayerBuffer final {
    friend class SceneSystem;

private:
    std::unordered_map<
        std::string_view,       //< Layer name (UNIQUE)
        std::unique_ptr<Layer>, //< Owned Layer
        misc::StringHash,
        misc::StringEq
    > _layers;

    constexpr LayerBuffer(LayerBuffer&&)                 noexcept = delete;
    constexpr LayerBuffer(const LayerBuffer&)            noexcept = delete;
    constexpr LayerBuffer& operator=(LayerBuffer&&)      noexcept = delete;
    constexpr LayerBuffer& operator=(const LayerBuffer&) noexcept = delete;

    LayerBuffer() = default;
    ~LayerBuffer() = default;

public:
    // Loads layer into the layer buffer
    void loadLayer(std::unique_ptr<Layer> layer);

    // Access Layer using their unique name
    [[nodiscard]]
    std::unique_ptr<Layer>& getLayer(std::string_view layer_name) noexcept;

    // DEV: Logs all loaded layer and all the nodes within those layers
    void logStats() const noexcept;
};

} // namespace dull::core
