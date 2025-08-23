#pragma once

#include "perceptron.hpp"
#include "../source/core/node.hpp"

#include <memory>

class InputHandler : public Node {
private:
    std::weak_ptr<Perceptron> _perceptron_ref;

    void _handleSwitchInput();
    void _handleWeightInput();

protected:
    void _init() final;
    void _update() final;

public:
    explicit InputHandler(std::string name) : Node(std::move(name)) {}
    ~InputHandler() override = default;
};