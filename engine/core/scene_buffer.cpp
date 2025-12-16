#include "engine/config.hpp"
#include "engine/core/scene_buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_LAYER_SYS)

SceneBuffer::SceneBuffer()
{
    _scenes.reserve(static_cast<size_t>(config::SceneID::_COUNT));
    _scenes.emplace_back(); // NULL SCENE
}

void SceneBuffer::loadScene(config::SceneID scene_id, std::unique_ptr<Scene> scene)
{
    _scenes.emplace_back(std::move(scene));
    _IF_LOG ZINFO("Scene '{}' loaded to SceneBuffer", static_cast<size_t>(scene_id));
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneBuffer::getScene(config::SceneID scene_id) noexcept
{
    size_t scene_index = static_cast<size_t>(scene_id);
    ZASSERT(_scenes.size() > scene_index, "The provided SceneID is out of range in the SceneBuffer");
    return _scenes[scene_index];
}

void SceneBuffer::logStats() const noexcept
{
    ZON_RELEASE return;
    for (const auto& SCENE : _scenes)
    {
        for (const auto& LAYER_CTX : SCENE->getLayers())
        {
            ZDBG(
                "{}{}{}",
                LAYER_CTX.first,
                zlog::config::TAG_TAG,
                (LAYER_CTX.second ? "ACTIVE" : "-")
            );
        }
    }
}

#undef _IF_LOG

} // namespace dull::core
