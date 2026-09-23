#pragma once

#ifdef GREVIR_FASTLED_HOST_MOCK
#include <grevir/fastled/mock.hpp>
#else
#include <FastLED.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef abs
#undef abs
#endif
#ifdef constrain
#undef constrain
#endif
#endif
