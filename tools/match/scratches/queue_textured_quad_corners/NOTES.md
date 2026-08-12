# OSDPrintUV (four-corner overload)

The long `OSDPrintUV` overload owns the Windows routine at `0x44aac0`. The
recovery is semantic-complete at 89.86%: 69/69 instructions and all 24
references clean.

It appends four explicit corner pairs and UV bounds; Android and iOS prove the
two otherwise unused pre-flag arguments are floats. Both ports retain the same
authored overload in `Font.o` and use a void return, while Windows locally
proves an incidental appended-byte offset. The remaining delta is aggregate
color/count publication and argument-load scheduling.

The directory and manifest retain `queue_textured_quad_corners` as the stable
matcher identifier; the VC6 decoration disambiguates the overload.
