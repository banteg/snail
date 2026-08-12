# attach_render_camera_source

The exact Windows body is the mobile-authored
`int cRViewport::SetCamera(cRCamera*)`: it stores a borrowed camera at viewport
`+0x20`, sets active flag bit 0 at `+0x08`, and returns the updated flags.
Android and iOS retain the same owner, name, parameter type, and one body each.

Its only Windows caller, `initialize_game_assets_and_world`, invokes it twice
on viewports 1 and 4 in the five-record array at `cRGame +0x5b4`. The arguments
are the cameras embedded in `cRPlayer[0]` and `cRPlayer[1]`; neither viewport
allocates or frees its camera.

Focused Wibo result: 100.00%, 6/6 instructions, no masked operands.
