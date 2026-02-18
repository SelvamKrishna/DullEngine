#pragma once

namespace dull::component {

struct Timer {
private:
    double _measureTime;
    double _startedTime = -1.0;

public:
    explicit Timer(double timeToMeasure) noexcept;

    void Start() noexcept;
    void Stop() noexcept;

    [[nodiscard]] bool IsActive() const noexcept;
    [[nodiscard]] bool IsOver() noexcept;
};

} // namespace dull::component
