#include "app/constants.hpp"

#include "engine/core/app.hpp"
#include "engine/utils/rect.hpp"
#include "engine/utils/input.hpp"
#include "engine/utils/color.hpp"

#include "template/component/camera2d.hpp"

#include "vendor/raylib.h"

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <vector>

/// A: UPDATE: app/constants.hpp; GameInfo::*
/// B: Implement your own render system
/// C: Implement your own physics system
/// D: Implement your own nodes

class RectPoolNode : public Node {
private:
	std::vector<rect> _rectangles;
	std::vector<color> _rectangle_color;

protected:
	void _init() final {
		const color COLOR_LIST[] = {RED, BLUE, GREEN, YELLOW};

		_rectangles.resize(100);
		_rectangle_color.resize(100);

		for (uint8_t i { 0 }; i < 100; i++) {
			_rectangles.emplace_back(rect{
				(float)(rand() % 1000),
				(float)(rand() % 1000),
				(float)(rand() % 100),
				(float)(rand() % 100)
			});

			_rectangle_color.emplace_back(COLOR_LIST[rand() % 4]);
		}
	}

	void _update() final {}

public:
	explicit RectPoolNode(std::string name) : Node(std::move(name)) {}
	~RectPoolNode() override = default;

	void addRect(rect rect) {
		_rectangles.push_back(rect);
	}

	[[nodiscard]] constexpr const std::vector<rect>& getRectangles() noexcept { return _rectangles; }
	[[nodiscard]] constexpr const std::vector<color>& getRectanglesColor() noexcept { return _rectangle_color; }
};

class SandboxRender : public RenderSystem {
private:
	void _init() final {
		cam.offset = { GameInfo::WINDOW_WIDTH / 2.0f, GameInfo::WINDOW_HEIGHT / 2.0f };
	}

	void _draw() final {
		constexpr int SPEED = 300;

		if (key{KeyCode::A}.isDown()) pos.x -= SPEED * D_TIME;
		if (key{KeyCode::D}.isDown()) pos.x += SPEED * D_TIME;
		if (key{KeyCode::W}.isDown()) pos.y -= SPEED * D_TIME;
		if (key{KeyCode::S}.isDown()) pos.y += SPEED * D_TIME;

		ClearBackground(BLACK);

		BeginMode2D(cam);

		if (auto rect_pool = CURRENT_SCENE.getNode<RectPoolNode>().lock()) {
			const auto& RECT = rect_pool->getRectangles();
			const auto& COL = rect_pool->getRectanglesColor();

			for (size_t i { 0 }; i < RECT.size(); i++) DrawRectangleRec(RECT[i], COL[i]);
		}

		EndMode2D();
	}

public:
	vec2 pos, other;
	camera2d_locked cam { pos };
};

int main(void) {
	auto& app { APP };

	SceneBuilder{}
		.newScene(1)
		.addNode<RectPoolNode>("rect-pool")
		.pushToSystem(GameInfo::SceneID::Level0, true);

	app.setRenderSystem(std::make_unique<SandboxRender>());
	app.run();
}