# `initialize_bass_audio_backend` recovery notes

Target: `initialize_bass_audio_backend @ 0x449460` (`thiscall`, returns `char`, `ret 0x4`).

This helper extracts `Bass.dll` from the game archive into `tBass.dll`, loads it with `LoadLibraryA`, resolves the BASS 2.0 function table through `GetProcAddress`, initializes the backend through `BASS_Init(1, 44100, 0, hwnd, 0)`, applies config option `1 = 50`, and clears the active stream handles.

The native code resolves `BASS_SetConfig` twice. The scratch keeps that duplicate store because it is present in the original instruction stream.

`AudioBackend` fields at `+4` and `+8` are still unnamed in the shared header, so the scratch writes them with raw offsets while using `is_paused` and `music_stream_active` for the known lanes.

## Source-shape findings

- Calling `GetProcAddress(g_bass_module, ...)` directly is required for the exact MSVC 6.5 shape. A local `module` variable makes the compiler keep the module handle in `esi` and save `ebp`, which diverges from the native function.
- The exact function keeps `GetProcAddress` in `esi`, reloads `g_bass_module` into `eax`/`ecx`/`edx` between export lookups, and keeps `this` in `edi`.
