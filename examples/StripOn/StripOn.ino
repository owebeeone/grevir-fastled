#include <GrevirArduinoAVR.h>
#include <GrevirFastLED.h>

using Strip = ardo_fastled::LedStrip<8, ardo::ExternalPin<6>, WS2812B, GRB, 16>;

class FillBlue : public ardo::ModuleBase<ardo::Parameters<>> {
public:
  static void runSetup() {
    for (unsigned i = 0; i < Strip::COUNT; ++i) {
      Strip::set(i, CRGB::Blue);
    }
  }
};

using App = ardo::ArduinoAvrApplication<Strip, FillBlue>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}
