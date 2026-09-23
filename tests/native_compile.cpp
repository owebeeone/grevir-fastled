#include <GrevirFastLED.h>
#include <GrevirPeripherals.h>

using Strip = ardo_fastled::LedStrip<10, ardo::ExternalPin<4>, WS2812B, GRB, 10>;
using App = ardo::Application<Strip>;

void instantiate_fastled() {
  App::runSetup();
  App::runLoop();
  Strip::set(0, CRGB::Blue);
  (void)Strip::get(0);
  Strip::setBrightness(20);
}
