#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace sm {

enum class EventType : uint8_t {
    Button = 0
};

struct Event {
    uint64_t frame{};
    EventType type{EventType::Button};
    uint8_t button{};
    bool pressed{};
};

class Macro {
public:
    static constexpr const char* Magic = "SM01";

    uint32_t fps = 240;
    std::vector<Event> events;

    bool save(std::string const& path) const;
    bool load(std::string const& path);
};

class Recorder {
public:
    void start(uint64_t frame);
    void stop();
    void button(uint64_t frame, uint8_t button, bool pressed);

    bool recording() const;
    Macro const& macro() const;

private:
    bool m_recording{};
    uint64_t m_startFrame{};
    Macro m_macro;
};

class Player {
public:
    void start(Macro const& macro, uint64_t frame);
    void stop();
    bool playing() const;
    void update(uint64_t frame);

private:
    bool m_playing{};
    uint64_t m_startFrame{};
    std::size_t m_nextEvent{};
    Macro m_macro;
};

} // namespace sm
