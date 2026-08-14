# OSDPrint

`OSDPrint(int, float, float, float, float, int, tColour, int)` owns the Windows
routine at `0x44a8b0`. The recovery is exact: 65/65
instructions and all 20 references clean.

It appends an axis-aligned textured quad with default UVs to the shared font
queue. Android and iOS both export the authored `Font.o` symbol. Mobile uses a
void return; Windows locally proves an incidental appended-byte offset.

The directory and manifest retain `queue_axis_aligned_textured_quad` as the
stable matcher identifier.

## 2026-08-14 exact queue and default-UV ownership

The append path now publishes the queue slot and its authored default UVs
directly through `g_font_queue[index]`. Removing the temporary entry owner
restores the native field order without changing behavior. Focused matching is
exactly 100.00% (`65/65`, prefix 65) with all 20 references clean.
