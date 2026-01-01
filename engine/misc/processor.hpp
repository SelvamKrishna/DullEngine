#pragma once

#include <string>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::misc {

// =======================
// Logic Processing interface
// =======================
class IProcessor {
    friend core::App;

protected:
    virtual void iStart()        = 0; // Called once
    virtual void iProcess()      = 0; // Called every frame
    virtual void iFixedProcess() = 0; // Called every fixed frame

    virtual ~IProcessor() = default;
};

// =======================
// IProcessor w/ Name support
// =======================
class INamedProcessor : public IProcessor {
    friend core::App;

protected:
    std::string _name; // Name of processor for identification

    INamedProcessor(std::string name) : _name {std::move(name)} {}
    virtual ~INamedProcessor() = default;

public:
    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }
};

} // namespace dull::misc
