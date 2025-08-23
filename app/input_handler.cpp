#include "input_handler.hpp"
#include "../source/core/app.hpp"
#include "../source/core/constants.hpp"

void InputHandler::_init() {
    _perceptron_ref = CURRENT_SCENE.getNode<Perceptron>();
}

void InputHandler::_handleSwitchInput() {
    if (auto perceptron = _perceptron_ref.lock()) [[likely]] {
        for (int y = 0; y < GameInfo::Custom::INPUT_PANEL_ROWS; y++) {
            for (int x = 0; x < GameInfo::Custom::INPUT_PANEL_COLS; x++) {
                int index = GameInfo::Custom::INPUT_PANEL_COLS * y + x;
                bool is_valid_press = CheckCollisionPointCircle(
                    GetMousePosition(), 
                    Vec2{
                        (float)GameInfo::Custom::SWITCH_OFFSET.x + x * GameInfo::Custom::SWITCH_SPACING,
                        (float)GameInfo::Custom::SWITCH_OFFSET.y + y * GameInfo::Custom::SWITCH_SPACING,
                    },
                    GameInfo::Custom::SWITCH_SIZE
                );

                if (is_valid_press) perceptron->flipSwitch(index);
            }
        }
    }
}

void InputHandler::_handleWeightInput() {
    if (auto perceptron = _perceptron_ref.lock()) [[likely]] {
        constexpr int WHEEL_MULT = 4;
        float wheel = GetMouseWheelMove();

        bool is_bias_hovering = CheckCollisionPointCircle(
            GetMousePosition(),
            Vec2{
                (float)GameInfo::Custom::PANEL_OFFSET.x + GameInfo::Custom::BIAS_COORD.x * GameInfo::Custom::PANEL_SPACING,
                (float)GameInfo::Custom::PANEL_OFFSET.y + GameInfo::Custom::BIAS_COORD.y * GameInfo::Custom::PANEL_SPACING
            },
            GameInfo::Custom::PANEL_SIZE
        );

        if (is_bias_hovering) {
            perceptron->setBias(perceptron->biasValue() + wheel * WHEEL_MULT);
            return;
        }
        
        for (int y = 0; y < GameInfo::Custom::INPUT_PANEL_ROWS; y++) {
            for (int x = 0; x < GameInfo::Custom::INPUT_PANEL_COLS; x++) {
                int index = GameInfo::Custom::INPUT_PANEL_COLS * y + x;
                
                bool is_hovering = CheckCollisionPointCircle(
                    GetMousePosition(),
                    Vec2{
                        (float)GameInfo::Custom::PANEL_OFFSET.x + x * GameInfo::Custom::PANEL_SPACING,
                        (float)GameInfo::Custom::PANEL_OFFSET.y + y * GameInfo::Custom::PANEL_SPACING,
                    },
                    GameInfo::Custom::PANEL_SIZE
                );
                
                if (is_hovering) {
                    perceptron->setWeight(
                        index,
                        perceptron->weightValue(index) + wheel * WHEEL_MULT
                    );
                    break;
                }
            }
        }
    }
}


void InputHandler::_update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) [[unlikely]] _handleSwitchInput();
    if (GetMouseWheelMove() != 0.0f) [[unlikely]] _handleWeightInput();
}