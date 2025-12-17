#include "engine/config.hpp"
#include "engine/core/scene_buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)
#define _AS_IDX(VAL)  static_cast<size_t>(VAL)

SceneBuffer::SceneBuffer()
{
    _scenes[_AS_IDX(config::SceneID::_NULL)] = std::make_unique<Scene>(); // NULL SCENE
}

void SceneBuffer::loadScene(config::SceneID scene_id, std::unique_ptr<Scene> scene)
{
    size_t scene_idx = _AS_IDX(scene_id);
    scene->_scene_id = scene_id;
    _scenes[scene_idx] = std::move(scene);

    _IF_LOG ZINFO("Scene '{}' loaded to SceneBuffer", scene_idx);
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneBuffer::getScene(config::SceneID scene_id) noexcept
{
    size_t scene_index = _AS_IDX(scene_id);
    ZASSERT(_scenes.size() > scene_index, "The provided SceneID is out of range in the SceneBuffer");
    return _scenes[scene_index];
}

void SceneBuffer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging SceneBuffer");
    for (const std::unique_ptr<Scene>& SCENE : _scenes) SCENE->logStats();
}

#undef _AS_IDX
#undef _IF_LOG

} // namespace dull::core
