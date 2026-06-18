# handle_game_window_activate

Runtime window reactivation helper at `0x4072f0`.

Recovered behavior:

- emits the two stripped debug report messages used by the native activation
  path;
- resumes the shared audio backend and clears the deactivation latch;
- reapplies fullscreen mode when the saved fullscreen config is enabled;
- refreshes the previous-frame timestamp, shows and focuses the main window,
  and clears both slots of the left/right mouse button state and latch arrays.

Focused match: 100%, 44/44 instructions, with 26 clean masked operands.

The stripped debug helper is declared as a fixed one-argument call here because
this native site only pushes the format pointer for each message. That lets
MSVC 6.5 coalesce the two cdecl cleanups into the native `add esp, 0x8`.
