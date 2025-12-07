#pragma once

#include "engine/core/layer.hpp"
#include "engine/misc/string_view_hashing.hpp"

#include <unordered_map>
#include <string>
#include <memory>

namespace dull::core {

class LayerBuffer final {
    friend class SceneSystem;

private:
    std::unordered_map<
        std::string,
        std::unique_ptr<Layer>,
        misc::StringHash,
        misc::StringEq
    > _layers;

    constexpr LayerBuffer(LayerBuffer&&)                 noexcept = delete;
    constexpr LayerBuffer(const LayerBuffer&)            noexcept = delete;
    constexpr LayerBuffer& operator=(LayerBuffer&&)      noexcept = delete;
    constexpr LayerBuffer& operator=(const LayerBuffer&) noexcept = delete;

    LayerBuffer() = default;
    ~LayerBuffer() = default;

    [[nodiscard]]
    std::unique_ptr<Layer>& getLayer(std::string_view layer_name) noexcept { return _layers[std::string{layer_name}]; }

public:
    void loadLayer(std::unique_ptr<Layer> layer);
};

} // namespace dull::core
