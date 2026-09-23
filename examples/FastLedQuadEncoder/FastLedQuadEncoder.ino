#include <GrevirArduinoAVR.h>
#include <GrevirFastLED.h>
#include <GrevirEncoder.h>

using QEncoder = quad::QuadEncoder<
  ardo::DebounceInput<ardo::arduino::InputPin<7>, ardo::ArduinoMillisClock>,
  ardo::DebounceInput<ardo::arduino::InputPin<8>, ardo::ArduinoMillisClock>>;
using QModule = quad::QuadEncoderModule<QEncoder>;
using Leds = ardo_fastled::LedStrip<10, ardo::ExternalPin<4>, WS2812B, GRB, 10>;

struct CombineModule : ardo::ModuleBase<ardo::Parameters<>> {
  static void runLoop() {
    auto pos = QModule::quadEncoder.getCurrentPosition();
    if (pos < 0) {
      pos = 0;
      QModule::quadEncoder.setCurrentPosition(pos);
    } else if (pos > 100) {
      pos = 100;
      QModule::quadEncoder.setCurrentPosition(pos);
    }
    for (unsigned i = 0; i < Leds::COUNT; ++i) {
      Leds::set(i, valueFor(static_cast<int>(i), pos));
    }
  }

  static CRGB valueFor(int led, long pos) {
    return led >= (pos / 10) ? CRGB::Red : CRGB::Blue;
  }
};

using App = ardo::ArduinoAvrApplication<QModule, Leds, CombineModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
