#pragma once

#include <vendor/zlog_v2.hpp>

#include <vector>
#include <functional>

namespace dull::core {

using LayerContext = std::pair<std::string_view, bool>;
using LayerGroup   = std::vector<std::string_view>;

class Scene final {
private:
    std::vector<LayerContext> _layers;
    bool _is_current = false;

public:
    explicit Scene() = default;
    explicit Scene(std::initializer_list<std::string_view> layers);

    void addLayer(std::string_view layer_name, size_t idx = UINT64_MAX, bool active = true);
    void removeLayer(size_t index);
    void removeLayer(std::string_view layer_name);

    [[nodiscard]]
    std::vector<LayerContext>& getLayers() noexcept { return _layers; }

    [[nodiscard]]
    LayerGroup getLayersBy(std::function<bool(const LayerContext&)> condition) noexcept;

    [[nodiscard]]
    LayerGroup getActiveLayers() noexcept;

    [[nodiscard]]
    LayerGroup getInactiveLayers() noexcept;

    [[nodiscard]]
    bool isLayerActive(std::string_view layer_name) noexcept;

    void setLayerActive(std::string_view layer_name, bool active) noexcept;
};

} // namespace dull::core
