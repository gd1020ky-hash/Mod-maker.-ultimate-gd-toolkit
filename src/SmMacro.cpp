#include "SmMacro.hpp"

#include <fstream>
#include <sstream>
#include <utility>

namespace sm {

bool Macro::save(std::string const& path) const {
    std::ofstream out(path);
    if (!out) return false;

    out << Magic << '\n';
    out << "FPS=" << fps << '\n';

    for (auto const& e : events) {
        out << "EVENT "
            << e.frame << ' '
            << static_cast<unsigned>(e.type) << ' '
            << static_cast<unsigned>(e.button) << ' '
            << (e.pressed ? 1 : 0) << '\n';
    }

    return static_cast<bool>(out);
}

bool Macro::load(std::string const& path) {
    std::ifstream in(path);
    if (!in) return false;

    Macro parsed;
    std::string line;

    if (!std::getline(in, line) || line != Magic)
        return false;

    while (std::getline(in, line)) {
        if (line.rfind("FPS=", 0) == 0) {
            try {
                parsed.fps = static_cast<uint32_t>(std::stoul(line.substr(4)));
            } catch (...) {
                return false;
            }
            continue;
        }

        if (line.rfind("EVENT ", 0) == 0) {
            std::istringstream ss(line.substr(6));
            Event e;
            unsigned type = 0;
            unsigned button = 0;
            unsigned pressed = 0;

            if (!(ss >> e.frame >> type >> button >> pressed))
                return false;

            if (type > 255 || button > 255 || pressed > 1)
                return false;

            e.type = static_cast<EventType>(type);
            e.button = static_cast<uint8_t>(button);
            e.pressed = pressed != 0;
            parsed.events.push_back(e);
        }
    }

    *this = std::move(parsed);
    return true;
}

void Recorder::start(uint64_t frame) {
    m_macro.events.clear();
    m_startFrame = frame;
    m_recording = true;
}

void Recorder::stop() {
    m_recording = false;
}

void Recorder::button(uint64_t frame, uint8_t button, bool pressed) {
    if (!m_recording) return;

    Event e;
    e.frame = frame >= m_startFrame ? frame - m_startFrame : 0;
    e.button = button;
    e.pressed = pressed;
    m_macro.events.push_back(e);
}

bool Recorder::recording() const {
    return m_recording;
}

Macro const& Recorder::macro() const {
    return m_macro;
}

void Player::start(Macro const& macro, uint64_t frame) {
    m_macro = macro;
    m_startFrame = frame;
    m_nextEvent = 0;
    m_playing = true;
}

void Player::stop() {
    m_playing = false;
}

bool Player::playing() const {
    return m_playing;
}

void Player::update(uint64_t frame) {
    if (!m_playing) return;

    uint64_t elapsed = frame >= m_startFrame ? frame - m_startFrame : 0;

    while (m_nextEvent < m_macro.events.size() &&
           m_macro.events[m_nextEvent].frame <= elapsed) {
        // Geometry Dash input dispatch will be connected in the
        // version-specific integration layer.
        ++m_nextEvent;
    }

    if (m_nextEvent >= m_macro.events.size())
        m_playing = false;
}

} // namespace sm
