# initialize_mouse_authored_scale_from_clip_rect

Small mouse-scaling initializer at 0x44bbb0. Both BN and IDA decompiles show it
caching the current clip rect into the shared RECT at 0x777d88 and then
initializing the authored mouse scale for 640x480 coordinates.

Exact match: 100.00%, 7/7 instructions, with the GetClipCursor import,
g_mouse_clip_rect, and update_mouse_authored_scale operands resolved.
