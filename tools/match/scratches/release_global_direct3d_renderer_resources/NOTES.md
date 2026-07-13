# release_global_direct3d_renderer_resources @ 0x411d70

Global Direct3D renderer teardown wrapper used by the window/input initializer's
failure paths and by `uninitialize_input_devices`.

- Binary Ninja finds four native callers: three failure exits in
  `initialize_game_window_and_input` and the input shutdown wrapper.
- Native is exactly `mov ecx, 0x4f7458; jmp 0x4116f0`: it binds the
  process-owned `g_direct3d_renderer` singleton and tail-calls the renderer-owned
  resource teardown entry point.
- Promoting this real function into the gameplay manifest also stops
  `initialize_game_window_and_input` from absorbing the wrapper into its target
  extent.
