# store_color4f @ 0x44dbb0

Exact 9/9-instruction void `tColour::Set(float, float, float, float)`.
The historical constructor mapping was wrong: the mobile constructor and
setter perform the same four RGBA stores, but the delayed-widget glow in
Android and iOS `cRBorder::Draw` specifically calls `Set` after default
construction. Windows makes the corresponding call at `0x4018bb`.

The real authored setter in `authored-abi-control/scratch.cpp` is independently
exact. Run it with:

```sh
uv run snail match scratch tools/match/scratches/store_color4f/authored-abi-control --full
```

The four-float constructor is the neighboring `0x44db60` body: its additional
receiver return is expected VC6 constructor code, not evidence against the
constructor mapping. See `../set_color_rgba/NOTES.md` for the matched caller
roles and the shared header's temporary compatibility naming.
