# Grevir FastLED

**Public API:** [Grevir FastLED](https://github.com/owebeeone/grevir-wz/blob/main/docs/api/fastled.md).
See [installation](https://github.com/owebeeone/grevir-wz/blob/main/docs/install.md) and
[supported platforms](https://github.com/owebeeone/grevir-wz/blob/main/docs/supported.md).
The workspace `/docs` is the current user-facing contract; development
checkpoints below are historical.

FastLED strip integration with a singleton controller claim.

## Development record (historical)

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
the return). The `extras/legacy` ParkLightsV2 copy is a source reference;
the current application port lives in the workspace's separate `parklights`
repository.
