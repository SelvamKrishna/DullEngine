#include "engine/misc/scene_builder.hpp"
#include "engine/misc/buffer.hpp"
#include "engine/process/world.hpp"

namespace dull::misc {

SceneBuilder::SceneBuilder(std::string scene_name, size_t reserve)
: _scene {std::make_unique<process::Scene>(std::move(scene_name))}
{
    _scene->_layers.reserve(reserve);
}

SceneBuilder& SceneBuilder::addLayer(std::string_view layer_name, bool active, size_t idx)
{
    _scene->addLayer(layer_name, idx, active);
    return *this;
}

SceneBuilder& SceneBuilder::addLayers(std::initializer_list<process::Scene::LayerConfig> layers)
{
    for (auto& LAYER_CFG : layers)
        addLayer(LAYER_CFG.layer_name, LAYER_CFG.is_active);

    return *this;
}

[[nodiscard]]
std::unique_ptr<process::Scene> SceneBuilder::build() noexcept
{
    ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);
    return std::move(_scene);
}

void SceneBuilder::pushToBuffer() noexcept
{
    ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);

    std::string name_copy = std::string{_scene->getName()};

    ZASSERT(
        process::World::getSceneBuffer().loadData(_scene->getName(), std::move(_scene)),
        "LayerBuffer failed to load Layer '{}'", name_copy
    );
}

} // namespace dull::misc
