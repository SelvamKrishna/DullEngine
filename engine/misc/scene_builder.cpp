#include "engine/misc/scene_builder.hpp"
#include "engine/misc/buffer.hpp"
#include "engine/process/world.hpp"

namespace dull::misc {

SceneBuilder::SceneBuilder(std::string scene_name)
: _scene {std::make_unique<process::Scene>(std::move(scene_name))}
{}

SceneBuilder& SceneBuilder::reserve(size_t capacity) noexcept
{
    _scene->_layers.reserve(capacity);
    return *this;
}

SceneBuilder& SceneBuilder::addLayer(std::string_view layer_name, size_t idx, bool active)
{
    _scene->addLayer(layer_name, idx, active);
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
    process::World::getSceneBuffer().loadData(_scene->getName(), std::move(_scene));
}

} // namespace dull::misc
