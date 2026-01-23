#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

#include <engine/util/rect.hpp>
#include <engine/util/color_rgba.hpp>

class Box : public dull::misc::IRenderCall {
private:
    void iDraw() const override { rl::DrawRectangleRec(rec, col); }

public:
    dull::util::Rect rec;
    dull::util::Color col;

    Box(dull::util::Rect rect, dull::util::Color color)
        : rec(rect)
        , col(color)
    {}
};

class Node1 : public dull::process::Node {
private:
    Box b { {10, 10, 25, 25}, {255, 255, 255} };
    dull::misc::PermanentRenderCall b_render {b};

    void iStart() override {
        is_fixed_process = false;
        b_render.setActive(true);
    }

    void iProcess() override {
        if (rl::IsKeyDown(rl::KEY_S)) b.rec.y += 50 * DULL_CTX.time_sys.getDeltaTime();
        if (rl::IsKeyPressed(rl::KEY_D)) b_render.setActive(true);
        if (rl::IsKeyPressed(rl::KEY_A)) b_render.setActive(false);
    }

public:
    explicit Node1(std::string name) : dull::process::Node {name} {}
    ~Node1() override { b_render.setActive(false); }
};

int main(void)
{
    dull::core::App app;
    const dull::core::HandleContext& CTX = DULL_CTX;

    CTX.audio_sys.setMasterVolume(0.5f);

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>("Node1")
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    CTX.processor.setCurrentScene(sc1);
    app.run();
}
