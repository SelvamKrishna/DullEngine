#pragma once

#include "engine/core/layer.hpp"
#include <unordered_map>
#include <string>
#include <memory>

namespace dull::core {

class LayerBuffer final {
private:
    std::unordered_map<std::string, std::shared_ptr<Layer>> _layers;

public:
    constexpr LayerBuffer(LayerBuffer&&)                 noexcept = delete;
    constexpr LayerBuffer(const LayerBuffer&)            noexcept = delete;
    constexpr LayerBuffer& operator=(LayerBuffer&&)      noexcept = delete;
    constexpr LayerBuffer& operator=(const LayerBuffer&) noexcept = delete;

    LayerBuffer() = default;
    ~LayerBuffer() = default;

    void loadLayer(const std::string& name, std::shared_ptr<Layer> layer);

    [[nodiscard]]
    std::shared_ptr<Layer> getLayer(const std::string& name) const;
};

} // namespace dull::core
