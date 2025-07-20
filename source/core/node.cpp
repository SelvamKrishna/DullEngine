#include "node.hpp"

#include <utility>

Node::Node(std::string name) : _name(std::move(name)) {}