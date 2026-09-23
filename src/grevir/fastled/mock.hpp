#pragma once

// Explicit host stand-in for FastLED.h. Never selected by an absent Arduino
// constant or by compiling without FastLED installed.

#include <cstdint>
#include <cstring>

enum EOrder : uint8_t { RGB = 0, RBG, GRB, GBR, BRG, BGR };

enum LEDColorCorrection : uint32_t { UncorrectedColor = 0xFFFFFFu };

struct CRGB {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  constexpr CRGB() = default;
  constexpr CRGB(uint8_t ir, uint8_t ig, uint8_t ib) : r(ir), g(ig), b(ib) {}

  constexpr bool operator==(const CRGB& rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b;
  }

  static const CRGB Red;
  static const CRGB Blue;
  static const CRGB Black;
};

inline constexpr CRGB CRGB::Red{255, 0, 0};
inline constexpr CRGB CRGB::Blue{0, 0, 255};
inline constexpr CRGB CRGB::Black{0, 0, 0};

template <uint8_t DATA_PIN, EOrder RGB_ORDER>
class WS2812B {};

class CLEDController {
public:
  CLEDController& setCorrection(LEDColorCorrection) {
    return *this;
  }
};

namespace grevir::fastled::mock {

inline constexpr unsigned kMaxLeds = 64;

struct State {
  unsigned add_calls = 0;
  unsigned pin = 0;
  unsigned count = 0;
  unsigned shows = 0;
  std::uint8_t brightness = 255;
  CRGB* leds = nullptr;
  CRGB copy[kMaxLeds]{};
};

inline State& state() {
  static State instance{};
  return instance;
}

inline void reset() {
  state() = State{};
}

} // namespace grevir::fastled::mock

class CFastLED {
public:
  template <
    template <uint8_t, EOrder> class Chipset,
    uint8_t DATA_PIN,
    EOrder RGB_ORDER>
  CLEDController& addLeds(CRGB* leds, int nLeds) {
    auto& recorded = grevir::fastled::mock::state();
    ++recorded.add_calls;
    recorded.pin = DATA_PIN;
    recorded.count = static_cast<unsigned>(nLeds);
    recorded.leds = leds;
    return controller;
  }

  void show() {
    auto& recorded = grevir::fastled::mock::state();
    ++recorded.shows;
    if (recorded.leds == nullptr) {
      return;
    }
    const unsigned n = recorded.count < grevir::fastled::mock::kMaxLeds
      ? recorded.count
      : grevir::fastled::mock::kMaxLeds;
    std::memcpy(recorded.copy, recorded.leds, n * sizeof(CRGB));
  }

  void setBrightness(std::uint8_t scale) {
    grevir::fastled::mock::state().brightness = scale;
  }

  std::uint8_t getBrightness() const {
    return grevir::fastled::mock::state().brightness;
  }

private:
  CLEDController controller{};
};

inline CFastLED FastLED{};
