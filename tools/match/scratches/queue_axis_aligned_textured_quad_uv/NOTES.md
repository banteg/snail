# OSDPrintUV (axis-aligned overload)

The short `OSDPrintUV` overload owns the Windows routine at `0x44a9b0`. The
recovery is exact: 66/66 instructions and all 20
references clean.

It appends an axis-aligned textured quad with explicit UV bounds. Android and
iOS both retain the same authored overload in `Font.o`. Mobile uses a void
return; Windows locally proves an incidental appended-byte offset.

The directory and manifest retain `queue_axis_aligned_textured_quad_uv` as the
stable matcher identifier; the VC6 decoration disambiguates the overload.

## 2026-08-14 exact queue-slot ownership

The append path now writes through `g_font_queue[index]` directly instead of
retaining a local record pointer. That source shape matches the queue's global
ownership and restores native field-publication scheduling. Focused matching
is exactly 100.00% (`66/66`, prefix 66) with all 20 references clean.
