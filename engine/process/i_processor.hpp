#pragma once

// Forward Declaration
namespace dull::core { struct App; }

namespace dull::process {

struct IProcessor {
    friend core::App;

protected:
    virtual ~IProcessor() = default;

    virtual void OnInit       () {}
    virtual void OnUpdate     () {}
    virtual void OnFixedUpdate() {}
    virtual void OnShutdown   () {}
};

struct VoidProcessor final : public IProcessor {
protected:
    void OnInit       () final {}
    void OnUpdate     () final {}
    void OnFixedUpdate() final {}
    void OnShutdown   () final {}
};

} // namespace dull::process
