# initialize_game_data_archive

- Resets archive/input startup globals, the tracked allocation counters, the
  text-input repeat state, and the registered sound-sample count.
- Loads `SnailMail.dat`, allocates the shared archive scratch pad and music
  memory buffer, initializes the two controller slots to authored coordinates
  `(640, 240)`, and samples the current clip cursor rectangle.
- `g_archive_startup_flag` (`0x53c7f4`) is only written here in the current
  map, so the name stays deliberately generic until another use explains it.
- Current focused match: 82.47%, 50/47 candidate instructions, with 18 clean
  masked operands and one real input-loop base mismatch. The remaining
  residual is the controller-slot reset loop: native keeps the induction base
  at `g_input_slot0_axis_y`, while the candidate is semantically equivalent
  but shifted by one dword and saves `esi` for the compare.
