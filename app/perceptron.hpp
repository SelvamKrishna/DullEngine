#pragma once

#include "../source/core/node.hpp"
#include "../source/core/constants.hpp"
#include <array>
#include <cstdint>

class Perceptron : public Node {
private:
    std::array<bool, GameInfo::Custom::TOTAL_INPUT> _input_switches;
    std::array<int8_t, GameInfo::Custom::TOTAL_INPUT> _input_weights;
    int8_t _bias_weight;
    int32_t _output;

protected:
    void _init() final {
        for (uint8_t i = 0; i < GameInfo::Custom::TOTAL_INPUT; i++) {
            _input_switches[i] = false;
            _input_weights[i] = 0;
            _bias_weight = 0;
            _output = 0;
        }
    }

    void _update() final {
        int32_t new_output = 0;

        for (uint8_t i = 0; i < GameInfo::Custom::TOTAL_INPUT; i++) 
            new_output += static_cast<int8_t>(_input_switches[i]) * _input_weights[i];

        _output = new_output + _bias_weight;
    }

public:
    explicit Perceptron(std::string name) : Node(std::move(name)) {}
    ~Perceptron() override = default;

    constexpr void flipSwitch(uint8_t index) noexcept { _input_switches[index] = !_input_switches[index]; }
    constexpr void setWeight(uint8_t index, int8_t new_weight) noexcept { _input_weights[index] = new_weight; }
    constexpr void setBias(int8_t new_weight) noexcept { _bias_weight = new_weight; }

    [[nodiscard]] constexpr bool switchState(uint8_t index) noexcept { return _input_switches[index]; }
    [[nodiscard]] constexpr int8_t weightValue(uint8_t index) noexcept { return _input_weights[index]; }
    [[nodiscard]] constexpr int8_t biasValue() noexcept { return _bias_weight; }
    [[nodiscard]] constexpr int32_t output() noexcept { return _output; }
};