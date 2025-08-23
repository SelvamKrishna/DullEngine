#include "perceptron_renderer.hpp"
#include "../source/core/app.hpp"
#include "../source/core/constants.hpp"
#include <string>

void PerceptronRenderer::_draw_input_switch(Vec2i coord, bool switch_state) {
    DrawCircle(
        GameInfo::Custom::SWITCH_OFFSET.x + coord.x * GameInfo::Custom::SWITCH_SPACING,
        GameInfo::Custom::SWITCH_OFFSET.y + coord.y * GameInfo::Custom::SWITCH_SPACING,
        GameInfo::Custom::SWITCH_SIZE,
        switch_state ? RED : BLACK
    );
}

void PerceptronRenderer::_draw_weight_panel(Vec2i coord, int8_t weight_val) {
    const int C_X = GameInfo::Custom::PANEL_OFFSET.x + coord.x * GameInfo::Custom::PANEL_SPACING;
    const int C_Y = GameInfo::Custom::PANEL_OFFSET.y + coord.y * GameInfo::Custom::PANEL_SPACING;

    const int RADIUS = GameInfo::Custom::PANEL_SIZE;

    float angle = (static_cast<float>(weight_val) / 127.0f) * 180.0f;

    Color color = weight_val >= 0 ? GREEN : BLUE;

    DrawCircleSector({ (float)C_X, (float)C_Y }, (float)RADIUS, -90.0f, -90.0f + angle, 32, color);
    DrawCircleLines(C_X, C_Y, RADIUS, DARKGRAY);
}

void PerceptronRenderer::_init() {
    _perceptron_ref = CURRENT_SCENE.getNode<Perceptron>();
}

void PerceptronRenderer::_update() {
    BeginDrawing();
    ClearBackground(WHITE);
    
    if (auto perceptron = _perceptron_ref.lock()) [[likely]] {
        for (int y = 0; y < GameInfo::Custom::INPUT_PANEL_ROWS; y++) {
            for (int x = 0; x < GameInfo::Custom::INPUT_PANEL_COLS; x++) {
                int index = GameInfo::Custom::INPUT_PANEL_COLS * y + x;
                _draw_input_switch(Vec2i{x, y}, perceptron->switchState(index));
                _draw_weight_panel(Vec2i{x, y}, perceptron->weightValue(index));
            }
        }

        _draw_weight_panel(GameInfo::Custom::BIAS_COORD, perceptron->biasValue());
        DrawText(
            std::to_string(perceptron->output()).c_str(), 
            300, 
            300, 
            24, 
            perceptron->output() > 0 ? GREEN : BLUE
        );
    }

    DrawFPS(10, 10);
    EndDrawing();
}