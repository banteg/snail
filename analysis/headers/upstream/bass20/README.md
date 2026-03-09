# Official BASS 2.0 Header

Source:

- `https://www.un4seen.com/download.php?bass20`
- `https://www.un4seen.com/files/bass20.zip`

Files in this directory:

- `bass.h`: the upstream C header from the official `bass20.zip` SDK
- `bass_bn_import.h`: a Binary Ninja import wrapper derived from `bass.h`
- `wtypes.h`: a tiny local shim so BN can parse the upstream header without a
  full Windows SDK include tree

Why both `bass.h` and `bass_bn_import.h` exist:

- `bass.h` is the untouched upstream source we recovered from the official SDK
- `bass_bn_import.h` only changes two things for BN import:
  - `#include <wtypes.h>` becomes `#include "wtypes.h"`
  - `unsigned __int64` becomes `unsigned long long`

Observed fit against the game:

- the shipped `tBass.dll` and archive `BASS.DLL` are byte-identical
- the shipped DLL reports `FileVersion = 2.0`
- the official SDK `bass.dll` is not byte-identical to the shipped DLL, so this
  is the right major-version header but not necessarily the exact same point build
- `bass_bn_import.h` parses in BN and exposes `100` named BASS functions, which
  matches the shipped named export surface
