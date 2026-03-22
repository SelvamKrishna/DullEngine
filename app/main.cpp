#include <engine/config.hpp>
#include <engine/core/engine.hpp>
#include <engine/core/processor.hpp>
#include <engine/render/draw_handle.hpp>

struct GameProcessor final : public dull::core::IProcessor {
    dull::util::Transform2D transform;

    void IInit() final
    {
        zen::core::Log(zen::core::DBG, {"DullEngine-{}", dull::config::GetVersionString()});
    }

    void IUpdate(const dull::util::GlobalAccessor& globals) final
    {
        dull::util::Vec2f motion = dull::util::Vec2f {
            (float) (rl::IsKeyDown(rl::KEY_D) - rl::IsKeyDown(rl::KEY_A)),
            (float) (rl::IsKeyDown(rl::KEY_S) - rl::IsKeyDown(rl::KEY_W))
        }.Normalized();

        transform.position += motion * 200.0F * globals.timeRef.GetDeltaTime();
    }

    void IFixedUpdate(const dull::util::GlobalAccessor&) final { }

    void IDraw(const dull::render::DrawHandle& drawHandle) final
    {
        drawHandle.DrawRectangle({0, 0, 25, 25}, {.TRANSFORM_PTR = &transform, .tintOverlay = rl::RED});
        drawHandle.DrawCircle(10, rl::GetMousePosition(), rl::BLUE);
    }

    void IShutdown() final {}
};

int main(void)
{
    dull::core::Engine _ {};

    dull::core::Engine::Init({
        .title          = "Application",
        .dimension      = {800, 600},
        .isVsync        = false,
        .isResizeable   = false,
    });

    GameProcessor game {};

    dull::core::Engine::Run({&game});
}
