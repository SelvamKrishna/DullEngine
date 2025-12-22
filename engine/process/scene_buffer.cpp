#include "engine/config.hpp"
#include "engine/process/scene_buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

SceneBuffer::SceneIt SceneBuffer::_findScene(std::string_view scene_name) noexcept
{
    return std::find_if(
        _scenes.begin(), _scenes.end(),
        [&scene_name](const std::unique_ptr<Scene>& scene)
        {
            return scene->_name == scene_name;
        }
    );
}

void SceneBuffer::loadScene(std::unique_ptr<Scene> scene)
{
    ZASSERT(
        _findScene(scene->_name) == _scenes.end(),
        "Scene '{}' already loaded into SceneBuffer", scene->_name
    );

    _IF_LOG ZINFO("Scene '{}' loaded into SceneBuffer", scene->_name);
    _scenes.emplace_back(std::move(scene));
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneBuffer::getScene(std::string_view scene_name) noexcept
{
    auto it = _findScene(scene_name);

    ZASSERT(
        it != _scenes.end(),
        "Scene '{}' not found in SceneBuffer", scene_name
    );

    return *it;
}

bool SceneBuffer::hasScene(std::string_view& scene_name) noexcept
{
    return _findScene(scene_name) != _scenes.end();
}

void SceneBuffer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging SceneBuffer");
    for (const std::unique_ptr<Scene>& SCENE : _scenes) SCENE->logStats();
}

#undef _IF_LOG

} // namespace dull::process
