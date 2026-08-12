# OSDPrint

`OSDPrint(int, float, float, float, float, int, tColour, int)` owns the Windows
routine at `0x44a8b0`. The recovery is semantic-complete at 98.46%: 65/65
instructions and all 20 references clean.

It appends an axis-aligned textured quad with default UVs to the shared font
queue. Android and iOS both export the authored `Font.o` symbol. Mobile uses a
void return; Windows locally proves an incidental appended-byte offset. The
remaining delta is independent store scheduling.

The directory and manifest retain `queue_axis_aligned_textured_quad` as the
stable matcher identifier.
