#pragma once

#include "engine/misc/processor.hpp"

#include <vendor/zlog_v2.hpp>

#include <vector>
#include <functional>

namespace dull::process {

// =======================
// LayerName : IsActive
// =======================
struct LayerCtx final {
    std::string_view layer_name; // Name of the Layer (UNIQUE), String stored within Layer
    bool             is_active;  // Is the layer active
};

using LayerGroup = std::vector<std::string_view>; //< List of LayerName's

// =======================
// Manager of all scene related logic
// =======================
class Scene final : private misc::IProcessor {
    friend class SceneProcessor;
    friend class SceneBuffer;

private:
    std::vector<LayerCtx> _layers; //< Collection of Layer Context
    std::string           _name;   //< Scene name (UNIQUE)

    void iStart() final;
    void iProcess() final;
    void iFixedProcess() final;

public:
    explicit Scene(std::string scene_name) noexcept : _name {std::move(scene_name)} {}

    // Add Layer with given Index(Process Order) and Activity
    void addLayer(std::string_view layer_name, size_t idx = UINT64_MAX, bool active = true);

    // Remove Layer from Scene
    void removeLayer(std::string_view layer_name);

    [[nodiscard]]
    std::vector<LayerCtx>& getLayers() noexcept { return _layers; }

    // Filters thru Layers with the provided condition
    [[nodiscard]]
    LayerGroup getLayersBy(std::function<bool(const LayerCtx&)> condition) noexcept;

    // Get all active Layers
    [[nodiscard]]
    LayerGroup getActiveLayers() noexcept;

    // Get all inactive Layers
    [[nodiscard]]
    LayerGroup getInactiveLayers() noexcept;

    // Map a function to all Active Layers
    using LayerMethod = const std::function<void(std::unique_ptr<class Layer>&)>;
    void forAllActiveLayers(LayerMethod& function) noexcept;

    // Checks wether a Layer is active within a Scene
    [[nodiscard]]
    bool isLayerActive(std::string_view layer_name) noexcept;

    // Set Layer active also calls Layer::_active() function when made alive
    void setLayerActive(std::string_view layer_name, bool active) noexcept;

    // DEV: logs all layer context
    void logStats() const noexcept;
};

} // namespace dull::process
