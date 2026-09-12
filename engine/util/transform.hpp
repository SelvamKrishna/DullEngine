#pragma once

#include <zen/math/angle.hpp>
#include <zen/math/vec2.hpp>

namespace dull::util {

    #define _BUILD_FN(_type, _name, _param_type, _param_name, _member) \
        [[nodiscard]] _type _name(_param_type _param_name) && { this->_member = _param_name; return std::move(*this); }

    struct Transform2D final {
        zen::vec2  position {0};
        zen::angle rotation {zen::angle::from_deg(0)};
        zen::vec2  scale    {1};

        _BUILD_FN(Transform2D, WithPosition, zen::vec2, position, position)
        _BUILD_FN(Transform2D, WithRotation, zen::angle, rotation, rotation)
        _BUILD_FN(Transform2D, WithScale, zen::vec2, scale, scale)

        [[nodiscard]] constexpr float GetScaleUnit() const noexcept { return zen::max(this->scale.x, this->scale.y); }
    };

    #undef _BUILD_FN

} // namespace dull::util
