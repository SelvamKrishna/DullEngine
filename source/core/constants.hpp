#pragma once

#include <cstdint>

namespace GameInfo {
	inline constexpr const char* TITLE = "Sandbox";

	inline constexpr int WINDOW_WIDTH  = 800;
	inline constexpr int WINDOW_HEIGHT = 800;

	inline constexpr float FIXED_FRAME_RATE = 60.0F;

	inline constexpr uint8_t TOTAL_SCENE_COUNT = 1;
	enum class SceneID : uint8_t {
		Level0,
	};

	/// MODIFY: Add your own constants here
	namespace Custom {

	}
}

namespace EngineInfo {
	inline constexpr uint8_t VERSION_MAJOR = 0;
	inline constexpr uint8_t VERSION_MINOR = 1;
}