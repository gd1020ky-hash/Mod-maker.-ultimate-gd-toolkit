#pragma once

#include "SmMacro.hpp"

namespace sm {

class Pathfinder {
public:
    bool running() const { return m_running; }
    void stop() { m_running = false; }

    // Produces a verified Macro when the Pathfinder integration is implemented.
    bool search(Macro& output);

private:
    bool m_running = false;
};

} // namespace sm
