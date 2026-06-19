# `initialize_bass_audio_backend` match result

## Score

| Metric | Value |
|---|---:|
| Match | **100.00%** |
| Target instructions | 176 |
| Candidate instructions | 176 |
| Common prefix | 176 / 176 |
| Masked operands | 87 clean, 0 unresolved, 0 mismatched |

This scratch matches exactly. The source keeps the original `GetProcAddress(g_bass_module, ...)` shape rather than caching the module handle locally; caching the module caused VC6 to save `ebp` and hold the module in `esi`, while the native code keeps `GetProcAddress` in `esi` and reloads `g_bass_module` for each export lookup.
