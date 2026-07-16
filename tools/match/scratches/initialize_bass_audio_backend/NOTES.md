# `initialize_bass_audio_backend` recovery notes

Target: `initialize_bass_audio_backend @ 0x449460` (`thiscall`, returns `char`, `ret 0x4`).

This helper extracts `Bass.dll` from the game archive into `tBass.dll`, loads it with `LoadLibraryA`, resolves the BASS 2.0 function table through `GetProcAddress`, initializes the backend through `BASS_Init(1, 44100, 0, hwnd, 0)`, applies config option `1 = 50`, and clears the active stream handles.

The native code resolves `BASS_SetConfig` twice. The scratch keeps that duplicate store because it is present in the original instruction stream.

2026-07-16 dispatch ownership pass:

- The resolver order and export strings prove all 23 function-pointer globals;
  the vendored official `analysis/headers/upstream/bass20/bass.h` supplies their
  exact BASS 2.0 `__stdcall` signatures.
- The exact signature surface now lives once in `audio_system.h`, replacing the
  scratch-local generic `BassProcFn` casts and the duplicated partial typedefs
  in downstream audio helpers. Rebuilding every transitive consumer remains
  instruction- and operand-exact.
- The loader imports keep ABI-exact raw `void *` module/procedure types. IDA's
  legacy Win32 TIL aliases otherwise leak an unrelated `ObjectFaceQuad` type
  into `LoadLibraryA`/`GetProcAddress` pseudocode; the raw declarations preserve
  the 32-bit `__stdcall` ABI without claiming that false ownership.
- `0x7517a0` is now canonically `g_bass_stream_play`, matching the resolved
  `BASS_StreamPlay` export. `0x753ca8` is now
  `g_bass_channel_is_active`, matching `BASS_ChannelIsActive`; the older
  channel-play and sample-is-active spellings remain aliases only.
- The 0x1c-byte unreferenced zero gap from `g_audio_backend + 0x1c` through
  `0x753c8f` does not prove that it belongs to `AudioBackend`. The independently
  resolved `g_bass_module` begins at `0x753c90`, so the live object remains
  deliberately unbound while only the proven prefix through `+0x18` is replayed.

`AudioBackend` fields at `+4` and `+8` remain semantically unnamed because no
independent consumer proves their roles. They are now structurally owned as
`unknown_04` and `unknown_08` in the shared header rather than written through
raw receiver offsets; initialization proves their types and values only.

## Source-shape findings

- Calling `GetProcAddress(g_bass_module, ...)` directly is required for the exact MSVC 6.5 shape. A local `module` variable makes the compiler keep the module handle in `esi` and save `ebp`, which diverges from the native function.
- The exact function keeps `GetProcAddress` in `esi`, reloads `g_bass_module` into `eax`/`ecx`/`edx` between export lookups, and keeps `this` in `edi`.

The structural field spelling remains exact at 176/176 instructions with all
87 masked operands clean.
