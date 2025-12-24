#include <engine/config.hpp>
#include <engine/core/app.hpp>

struct Circle {
    dull::util::Vec2f center;
    float radius;
};

Circle c {
    .center = {100, 200},
    .radius = 10
};

dull::util::Vec2f dir = {400, 400};

void Update()
{
    c.center += dir * DULL_CTX.time_sys.getDeltaTime();

    if (
        c.center.y - c.radius <= 0 ||
        c.center.y + c.radius >= dull::config::WINDOW_SIZE.y
    ) dir.y *= -1;

    if (
        c.center.x - c.radius <= 0 ||
        c.center.x + c.radius >= dull::config::WINDOW_SIZE.x
    ) dir.x *= -1;

    rl::DrawCircleV(c.center, c.radius, rl::WHITE);
}

void FixedUpdate()
{
    if (rl::IsMouseButtonDown(rl::MOUSE_BUTTON_LEFT)) [[unlikely]]
    {
        rl::Vector2 m_pos = rl::GetMousePosition();
        c.center = {m_pos.x, m_pos.y};
    }
}

int main(void)
{
    dull::core::App app = { dull::core::AppContext {} };

    const auto& DULL = DULL_CTX;

    DULL.processor.onStart([]() {
        ZDBG("Hello World");
    });

    DULL.processor.onProcess(Update);
    DULL.processor.onFixedProcess(FixedUpdate);

    app.run();
}
