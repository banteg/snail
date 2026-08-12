# FontInit

`FontInit()` is the native-authored owner of the Windows routine at `0x449c70`.
The focused match is exact: 5/5 instructions and four clean references.

It seeds both font-wave phases and their per-frame steps. Android and iOS both
export `FontInit()` from `Font.o`, and the live Windows database has one caller
in game asset/world initialization.

The directory and manifest retain `initialize_font_wave_state` as the stable
matcher identifier; source and linkage use the recovered authored name.
