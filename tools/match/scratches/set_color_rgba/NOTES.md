# set_color_rgba @ 0x44db60

This is the authored `tColour(float, float, float, float)` constructor, exact
at 10/10 Windows instructions. Its receiver return is the ordinary VC6
constructor ABI. The earlier mapping to four-argument `Set` was incorrect:
both mobile helpers store the same four lanes, which alone does not distinguish
construction from mutation.

## 2026-09-07 caller-role correction

The iOS `cRBorder::Draw` export at `0x391a0` and Android export at `0x5f5b0`
call the four-float constructor for the black shadow with alpha 0.9. Their
later delayed-widget glow explicitly default-constructs a colour and then
calls `Set(white.r, white.g, white.b, 1 - progress)`. The corresponding Windows
calls are `0x4014b7 -> 0x44db60` for the shadow and `0x4018bb -> 0x44dbb0`
for the glow. Both mobile `cRStarManager::Init` bodies independently construct
the same `(0.8, 0.8, 1.0, 0.4)` temporary seen at Windows `0x4345aa`.

The real constructor in `authored-abi-control/scratch.cpp` reproduces all ten
instructions, including `mov eax, ecx`. Run it with:

```sh
uv run snail match scratch tools/match/scratches/set_color_rgba/authored-abi-control --full
```

The adjacent setter and folded default constructor have equivalent controls
under their own scratch directories, matching 9/9 and 2/2 instructions.
These controls target existing functions and add no dashboard entries.

`sprite.h` retains the old explicit-receiver declaration as a compatibility
transcription, clearly marked as such. Adopting automatic construction across
the complete class also affects caller return buffers, which remains separate
source recovery. The verified mobile crosswalk and reference aliases now use
the corrected roles; no normalizer, compiler, extent, or score rule changed.

Actual constructor/default-constructor caller overlays preserve Draw at
99.72%, 712/712 instructions and 68 clean references, and StarManager::Init at
98.38%, 247/247 and 26 clean references. A Draw const-reference API diagnostic
has the same instructions but 23 uncurated call references, and is not retained.
The constructor interpretation does not by itself solve either residual.
