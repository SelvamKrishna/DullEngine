#pragma once

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

} // namespace dull::misc
