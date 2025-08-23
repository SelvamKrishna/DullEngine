#pragma once

#include "perceptron.hpp"
#include "../source/plugins/render_system.hpp"
#include "../source/utils/vec2.hpp"

#include <cstdint>
#include <memory>

class PerceptronRenderer : public RenderSystem {
private:
    std::weak_ptr<Perceptron> _perceptron_ref;

    void _draw_input_switch(Vec2i coord, bool switch_state);
    void _draw_weight_panel(Vec2i coord, int8_t weight_val);

    void _init() final;
    void _update() final;
};