#pragma once

#include <grevir/core/module.hpp>
#include <grevir/core/resource_claims.hpp>
#include <grevir/fastled/fastled_api.hpp>
#include <grevir/base/compat/cstdint.hpp>

namespace ardo_fastled {

/**
 * Exclusive claim on the FastLED controller singleton. Two strips in one
 * application fail Core's resource check.
 */
class FastLEDParameter {
private:
  FastLEDParameter() = delete;
public:
  using Claims = ardo::ResourceClaim<decltype(FastLED)>;

  inline static void runSetup() {}
  inline static void runLoop() {}
};

template <
  unsigned w_count,
  typename w_LedPin,
  template <uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
>
class LedStrip : public ardo::ModuleBase<ardo::Parameters<w_LedPin, FastLEDParameter>> {
public:
  constexpr static unsigned COUNT = w_count;
  constexpr static EOrder COLOR_ORDER = w_colorOrder;
  using LedPin = w_LedPin;

  static void runSetup() {
    instance.instanceSetup();
  }

  void instanceSetup() {
    FastLED.addLeds<w_Type, LedPin::PIN, COLOR_ORDER>(leds, COUNT).setCorrection(UncorrectedColor);
    FastLED.setBrightness(w_brightness);
  }

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (has_changed) {
      FastLED.show();
      has_changed = false;
    }
  }

  static void set(unsigned index, const CRGB& value) {
    instance.instanceSet(index, value);
  }

  static CRGB get(unsigned index) {
    return instance.instanceGet(index);
  }

  void instanceSet(unsigned index, const CRGB& value) {
    auto& entry = leds[index];
    if (entry == value) {
      return;
    }
    entry = value;
    has_changed = true;
  }

  CRGB instanceGet(unsigned index) const {
    return leds[index];
  }

  static void setBrightness(std::uint8_t scale) {
    instance.instanceSetBrightness(scale);
  }

  void instanceSetBrightness(std::uint8_t scale) {
    if (FastLED.getBrightness() == scale) {
      return;
    }
    FastLED.setBrightness(scale);
    has_changed = true;
  }

private:
  bool has_changed = true;
  CRGB leds[COUNT];

public:
  static LedStrip instance;
};

template <
  unsigned w_count,
  typename w_LedPin,
  template <uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
>
LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>
LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>::instance;

} // namespace ardo_fastled
