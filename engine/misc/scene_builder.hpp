#pragma once

#include "engine/process/layer.hpp"
#include "engine/process/scene.hpp"
#include "engine/process/world.hpp"
#include "engine/misc/buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

class SceneBuilder {
private:
    std::unique_ptr<process::Scene> _scene;

public:
    explicit SceneBuilder(std::string scene_name)
    : _scene {std::make_unique<process::Scene>(std::move(scene_name))}
    {}

    SceneBuilder& reserve(size_t capacity) noexcept
    {
        _scene->_layers.reserve(capacity);
        return *this;
    }

    [[nodiscard]]
    std::unique_ptr<process::Scene> build() noexcept
    {
        ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);
        return std::move(_scene);
    }

    void pushToBuffer() noexcept
    {
        ZASSERT(_scene != nullptr, "SceneBuilder::{} called more than once", __func__);
        process::World::getSceneBuffer().loadData("TODO: ", std::move(_scene));
    }
};

} // namespace dull::misc
