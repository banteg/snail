# release_direct3d_renderer_resources @ 0x4116f0

Renderer-owned teardown entry point reached only by the global singleton wrapper
at `0x411d70`.

Native is a single tail jump to `release_direct3d_device_interfaces` at
`0x411960`; because this is a member-to-member tail call, the incoming
`Direct3DRenderer*` remains in `ECX` unchanged.
