# OSDPrintUV (axis-aligned overload)

The short `OSDPrintUV` overload owns the Windows routine at `0x44a9b0`. The
recovery is semantic-complete at 98.48%: 66/66 instructions and all 20
references clean.

It appends an axis-aligned textured quad with explicit UV bounds. Android and
iOS both retain the same authored overload in `Font.o`. Mobile uses a void
return; Windows locally proves an incidental appended-byte offset. The
remaining delta is independent store scheduling.

The directory and manifest retain `queue_axis_aligned_textured_quad_uv` as the
stable matcher identifier; the VC6 decoration disambiguates the overload.
