# Binary Ninja Import Headers

This directory holds small handwritten headers for Binary Ninja import.

Import `snail_bn_import.h` in Binary Ninja. It is a flattened entrypoint because
BN's file importer does not reliably resolve sibling `#include` paths.

The split `*_min.h` files are the maintained sources behind that entrypoint:

- `win32_min.h`: 32-bit Win32 and COM base types used by the game
- `d3d8_min.h`: the Direct3D 8 surface currently recovered around `initialize_d3d8_device`
- `dinput8_min.h`: the DirectInput 8 surface currently recovered around keyboard, mouse, and controller setup
- `bass_min.h`: the BASS 2.0-era API subset resolved dynamically from `tBass.dll`

These are intentionally minimal. They are meant to make imported APIs, COM
vtables, and function-pointer wrappers readable in Binary Ninja, not to replace
the full DirectX or BASS SDK headers.

Current high-value targets for these headers:

- `initialize_d3d8_device`
- `enumerate_input_controllers`
- `initialize_keyboard_input`
- `initialize_mouse_input`
- `sub_449460` (`tBass.dll` loader)

Observed DLL facts behind `bass_min.h`:

- `tBass.dll` and the archive `BASS.DLL` are byte-for-byte identical
- the version resource reports `FileVersion = 2.0`
- the exported surface is still the older pre-2.1 API family used by the game

Why this lives in-repo:

- no local Windows SDK headers were installed on this machine
- we only want the parts the game actually uses
- keeping the headers here makes them easy to extend as RE improves
- the `crimson/third_party/headers` bundle is a useful same-era reference set, but
  these copies stay curated and much smaller for BN import
