# initialize_game_window_and_input @ 0x4119d0

Initial recovery for the Win32 window/input startup helper.

- Picks one of the recovered 4:3 resolution presets from `data_4df94c`,
  defaulting back to 640x480 when the setting is out of range.
- Registers `"SnailMailWindowClass"` with `game_window_proc`, then creates the
  main window, initializes the renderer, keyboard, controllers, and mouse, and
  sets cull mode.
- The caller passes the current fullscreen-active byte as a second argument to
  `initialize_mouse_input`; that callee only reads the first stack argument, but
  the extra push is part of this caller's native shape.

Focused match result: 79.85% (`287` target instructions, `264` candidate
instructions), with `42` masked operands resolved and `8` still unresolved.

Remaining gaps are mostly code-layout shape rather than unknown behavior:

- MSVC hoists the `0x400` constant into `ebp` for the render-depth test instead
  of emitting the native immediate `and esi, 0x400`.
- The native switch stores the authored width in each case block; this scratch
  still lets the compiler sink that store to the common path.
- The fullscreen fallback and common window-creation block are equivalent, but
  the compiler lays out the out-of-line fullscreen path earlier than native.
