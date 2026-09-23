#include <GrevirFastLED.h>
#include <GrevirPeripherals.h>

#if CASE_ID == 0
using App = ardo::Application<
  ardo_fastled::LedStrip<8, ardo::ExternalPin<4>, WS2812B, GRB, 10>>;
#elif CASE_ID == 1
struct ExtraPin : ardo::ModuleBase<ardo::Parameters<ardo::ExternalPin<7>>> {};
using App = ardo::Application<
  ardo_fastled::LedStrip<8, ardo::ExternalPin<4>, WS2812B, GRB, 10>,
  ExtraPin>;
#elif CASE_ID == 2
using First = ardo_fastled::LedStrip<8, ardo::ExternalPin<4>, WS2812B, GRB, 10>;
using Second = ardo_fastled::LedStrip<8, ardo::ExternalPin<5>, WS2812B, RGB, 10>;
using App = ardo::Application<First, Second>;
#elif CASE_ID == 3
struct SamePin : ardo::ModuleBase<ardo::Parameters<ardo::ExternalPin<4>>> {};
using App = ardo::Application<
  ardo_fastled::LedStrip<8, ardo::ExternalPin<4>, WS2812B, GRB, 10>,
  SamePin>;
#else
#error "unknown CASE_ID"
#endif

void instantiate() {
  App::runSetup();
  App::runLoop();
}
