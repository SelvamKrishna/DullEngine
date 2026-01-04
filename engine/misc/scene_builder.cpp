#include "engine/misc/scene_builder.hpp"
#include "engine/process/world.hpp"

namespace dull::misc {

SceneBuilder::SceneBuilder(std::string scene_name, size_t reserve)
: _scene {std::make_unique<process::Scene>(std::move(scene_name), reserve)}
{}

SceneBuilder& SceneBuilder::addLayer(
    process::Layer::ID layer_id, bool active, std::optional<size_t> idx
)
{
    _scene->addLayer(layer_id, active, idx);
    return *this;
}

SceneBuilder& SceneBuilder::addLayers(std::initializer_list<process::Scene::LayerConfig> layers)
{
    for (const process::Scene::LayerConfig& LAYER_CFG : layers)
        addLayer(LAYER_CFG.layer_id, LAYER_CFG.is_active);
    return *this;
}

[[nodiscard]]
std::unique_ptr<process::Scene> SceneBuilder::build() noexcept
{
    ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);
    return std::move(_scene);
}

process::Scene::ID SceneBuilder::pushToBuffer() noexcept
{
    ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);

    process::Scene::ID scene_id = _scene->getID();
    std::string name_copy = std::string{_scene->getName()};

    ZASSERT(
        process::World::getSceneBuffer().add(std::move(_scene)),
        "LayerBuffer failed to load Layer '{}'", name_copy
    );

    return scene_id;
}

} // namespace dull::misc
