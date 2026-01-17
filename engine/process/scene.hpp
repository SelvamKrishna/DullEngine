#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/misc/processor.hpp"
#include "engine/process/layer.hpp"

#include <vector>
#include <functional>

//Forward Declaration
namespace dull::misc { class SceneBuilder; }

namespace dull::process {

struct SceneTag final {};

// =======================
// Manager of all scene related logic
// =======================
class Scene final : private misc::IProcessor, public misc::Identified<SceneTag> {
    friend core::App;
    friend class World;
    friend class misc::SceneBuilder;

public:
    // =======================
    // Configuration of a Layer within Scene
    // =======================
    class LayerConfig final {
    public:
        Layer::ID layer_id;  //< Uinque ID of the layer
        bool      is_active; //< Is the layer active

        LayerConfig(Layer::ID layer_id, bool is_active)
        : layer_id {layer_id}, is_active {is_active}
        {}
    };

private:
    static misc::Buffer<Layer> s_layer_buf; //< Static owned buffer of all loaded Layers
    std::vector<LayerConfig>   _layers;     //< Ref of Layers within scene

    using LayerIt      = std::vector<LayerConfig>::iterator;
    using LayerConstIt = std::vector<LayerConfig>::const_iterator;

    void iStart()        final;
    void iProcess()      final;
    void iFixedProcess() final;

    [[nodiscard]]
    LayerIt _searchLayer(Layer::ID layer_id) noexcept;

    [[nodiscard]]
    LayerConstIt _searchLayer(Layer::ID layer_id) const noexcept;

    [[nodiscard]]
    std::string_view _getLayerName(Layer::ID layer_id) const noexcept;

public:
    using LayerGroup = std::vector<Layer::ID>; //< List of Layer's

    static constexpr size_t DEFAULT_NO_OF_LAYERS = 16;

    Scene(std::string name, size_t reserve = DEFAULT_NO_OF_LAYERS);

    static misc::Buffer<Layer>& getLayerBuffer() noexcept { return s_layer_buf; }

    // Add Layer with given Index(Process Order) and Activity
    void addLayer(Layer::ID layer_id, bool active = true, std::optional<size_t> idx = std::nullopt);

    // Remove Layer from Scene
    void removeLayer(Layer::ID layer_id);

    [[nodiscard]]
    std::vector<LayerConfig>& getLayers() noexcept { return _layers; }

    // Filters thru Layers with the provided condition
    [[nodiscard]]
    LayerGroup getLayersBy(std::function<bool(const LayerConfig&)> condition) noexcept;

    // Get all active Layers
    [[nodiscard]]
    LayerGroup getActiveLayers() noexcept;

    // Get all inactive Layers
    [[nodiscard]]
    LayerGroup getInactiveLayers() noexcept;

    // Map a function to all Active Layers
    using LayerMethod = const std::function<void(class Layer&)>;
    void forAllActiveLayers(LayerMethod& function) noexcept;

    // Checks wether a Layer is active within a Scene
    [[nodiscard]]
    bool isLayerActive(Layer::ID layer_id) noexcept;

    // Set Layer active also calls Layer::_active() function when made alive
    void setLayerActive(Layer::ID layer_id, bool active) noexcept;
};

} // namespace dull::process
