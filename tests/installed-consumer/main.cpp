#define GREVIR_FASTLED_HOST_MOCK
#include <GrevirFastLED.h>
#include <GrevirPeripherals.h>

using Strip = ardo_fastled::LedStrip<2, ardo::ExternalPin<4>, WS2812B, GRB, 10>;
using App = ardo::Application<Strip>;

int main() {
  grevir::fastled::mock::reset();
  App::runSetup();
  if (grevir::fastled::mock::state().pin != 4 ||
      grevir::fastled::mock::state().count != 2) {
    return 1;
  }
  Strip::set(0, CRGB::Red);
  App::runLoop();
  if (!(grevir::fastled::mock::state().copy[0] == CRGB::Red)) {
    return 2;
  }
  return 0;
}
