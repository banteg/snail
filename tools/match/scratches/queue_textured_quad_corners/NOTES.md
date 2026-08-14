# OSDPrintUV (four-corner overload)

The long `OSDPrintUV` overload owns the Windows routine at `0x44aac0`. The
recovery is exact: 69/69 instructions and all 24
references clean.

It appends four explicit corner pairs and UV bounds; Android and iOS prove the
two otherwise unused pre-flag arguments are floats. Both ports retain the same
authored overload in `Font.o` and use a void return, while Windows locally
proves an incidental appended-byte offset.

The directory and manifest retain `queue_textured_quad_corners` as the stable
matcher identifier; the VC6 decoration disambiguates the overload.

## 2026-08-14 exact record-publication ownership

The four-corner append now writes the selected global queue slot directly and
publishes `g_font_queue_count = index + 1` only after the complete record,
including blend mode and rotation, is initialized. That ownership boundary
recovers native color/count scheduling. Focused matching is exactly 100.00%
(`69/69`, prefix 69) with all 24 references clean.
