# Grevir FastLED

FastLED strip module and exclusive controller claim, extracted from Ardoinus
`ardOFastLED`. The unused time include is dropped. Pins are injected, typically
`ardo::ExternalPin<N>` because FastLED owns GPIO setup.

Host tests define `GREVIR_FASTLED_HOST_MOCK`. Production sketches install FastLED
from Arduino Library Manager. On weftpi with Debian `avr-g++` 14.2, pin
**FastLED 3.7.8** (`arduino-cli lib install FastLED@3.7.8`). FastLED 3.10.5
builds with stock Arduino avr-gcc 7.3 but its AVR clockless `_dc` templates fail
under gcc 14. Include `GrevirArduinoAVR.h` before `GrevirFastLED.h`.

```cpp
#include <GrevirArduinoAVR.h>
#include <GrevirFastLED.h>

using Strip = ardo_fastled::LedStrip<8, ardo::ExternalPin<6>, WS2812B, GRB, 16>;
using App = ardo::ArduinoAvrApplication<Strip>;
```

Two `LedStrip` modules in one `Application` fail with a FastLED resource
conflict. `get()` returns the stored colour (the original static getter dropped
the return). ParkLightsV2 stays under `extras/legacy` and is not the first
Arduino example.
