# show_and_focus_game_window

Startup window presentation helper at `0x4073b0`.

Recovered behavior:

- refreshes the previous-frame timestamp from `timeGetTime() * 0.001f`;
- shows the main window normally, brings it forward, focuses it, and activates
  it;
- clears both slots of the left/right mouse button state and latch arrays.

Focused match: 100%, 33/33 instructions, with 19 clean masked operands.
