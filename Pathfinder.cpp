#include "Pathfinder.hpp"

namespace sm {

bool Pathfinder::search(Macro& output) {
    m_running = true;

    // Future implementation:
    // 1. sample game state,
    // 2. generate candidate inputs,
    // 3. test candidates,
    // 4. detect failure/success,
    // 5. retry/search,
    // 6. save the verified route as a normal .sm macro.

    output.events.clear();
    m_running = false;
    return false;
}

} // namespace sm
