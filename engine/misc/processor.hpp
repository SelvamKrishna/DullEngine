#pragma once

// Forward Declaration
namespace dull::core { class App; }

namespace dull::misc {

class IProcessor {
    friend class App;

public:
    virtual void iStart() = 0;
    virtual void iProcess() = 0;
    virtual void iFixedProcess() = 0;

    virtual ~IProcessor() = default;
};

} // namespace dull::misc
