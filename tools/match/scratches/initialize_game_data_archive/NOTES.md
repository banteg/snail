# initialize_game_data_archive

- Resets archive/input startup globals, the tracked allocation counters, the
  text-input repeat state, and the registered sound-sample count.
- Loads `SnailMail.dat`, allocates the shared archive scratch pad and music
  memory buffer, initializes the two controller slots to authored coordinates
  `(640, 240)`, and samples the current clip cursor rectangle.
- `g_archive_startup_flag` (`0x53c7f4`) is only written here in the current
  map, so the name stays deliberately generic until another use explains it.
- Current focused match: 94.74%, 48/47 candidate instructions. The controller
  reset loop is best expressed as a byte cursor seeded from
  `g_input_slot0_buttons - 4`, which lands on the native `axis_y` base without
  forcing an unrelated scalar global declaration.
- `g_input_controller_slots_end` names the `0x5033b0` one-past sentinel for the
  two 0x38-byte controller slots. The sentinel follows from the recovered lane
  arrays (`slot 1 == slot 0 + 0x38`) and the native loop compare after the
  second slot.
- Remaining residual is source-shape scheduling: MSVC hoists the candidate
  cursor setup before the allocator-call stack cleanup as `mov eax,
  g_input_slot0_buttons; sub eax, 4`, while the native listing materializes the
  already-shifted `g_input_slot0_axis_y` after `add esp, 0x10`.
- Rejected follow-ups: using `g_input_controller_slots_end` as a C extern
  regressed the loop to 79.17%; using a direct `g_input_slot0_axis_y` byte
  cursor regressed to the old 82.47% `esi`/`axis_y + 4` shape. The raw
  sentinel immediate is kept in C, but the reference table now names it so the
  mask audit stays clean.
- 2026-06-20 larger-chunk retries: the decompiler-style float cursor and the
  direct `g_input_slot0_axis_y` integer cursor both reproduce the 82.47%
  `esi`/`axis_y + 4` regression. Spelling the current byte cursor as
  `g_input_slot0_buttons - 1` is codegen-neutral at 94.74%, while the
  one-before-axis variant shifts the physical stores and drops below baseline.
  The retained byte cursor remains the best evidence-backed source shape.
