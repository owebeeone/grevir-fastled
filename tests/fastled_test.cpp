#include <GrevirFastLED.h>
#include <GrevirPeripherals.h>
#include <catch2/catch_test_macros.hpp>

using Strip = ardo_fastled::LedStrip<4, ardo::ExternalPin<6>, WS2812B, GRB, 32>;
using App = ardo::Application<Strip>;

TEST_CASE("LedStrip setup registers the pin and brightness") {
  grevir::fastled::mock::reset();
  App::runSetup();
  REQUIRE(grevir::fastled::mock::state().add_calls == 1);
  REQUIRE(grevir::fastled::mock::state().pin == 6);
  REQUIRE(grevir::fastled::mock::state().count == 4);
  REQUIRE(grevir::fastled::mock::state().brightness == 32);
}

TEST_CASE("First loop shows the default black buffer") {
  grevir::fastled::mock::reset();
  App::runSetup();
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 1);
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 1);
}

TEST_CASE("set writes CRGB and show copies on change") {
  grevir::fastled::mock::reset();
  App::runSetup();
  Strip::set(1, CRGB::Blue);
  REQUIRE(Strip::get(1) == CRGB::Blue);
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 1);
  REQUIRE(grevir::fastled::mock::state().copy[1] == CRGB::Blue);
  Strip::set(1, CRGB::Blue);
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 1);
  Strip::set(1, CRGB::Red);
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 2);
  REQUIRE(grevir::fastled::mock::state().copy[1] == CRGB::Red);
}

TEST_CASE("setBrightness marks the strip dirty") {
  grevir::fastled::mock::reset();
  App::runSetup();
  App::runLoop();
  Strip::setBrightness(8);
  REQUIRE(grevir::fastled::mock::state().brightness == 8);
  App::runLoop();
  REQUIRE(grevir::fastled::mock::state().shows == 2);
}
