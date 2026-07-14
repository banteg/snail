# initialize_game_data_archive

- Resets archive/input startup globals, the tracked allocation counters, the
  text-input repeat state, and the registered sound-sample count.
- Loads `SnailMail.dat`, allocates the shared archive scratch pad and music
  memory buffer, initializes the two controller slots to authored center
  coordinates `(320, 240)`, and samples the current clip cursor rectangle.
- `g_archive_startup_flag` (`0x53c7f4`) is only written here in the current
  map, so the name stays deliberately generic until another use explains it.
- Current focused match: 94.74%, 48/47 candidate instructions. The controller
  reset loop is best expressed as a byte cursor seeded from
  `g_input_slot0_buttons - 4`, which lands on the native `axis_y` base without
  forcing an unrelated scalar global declaration.
- `g_input_slot_axis_y_end` names the `0x5033b0` one-past sentinel for the
  loop's axis-y cursor over two 0x38-byte controller slots. The complete typed
  array itself ends four bytes earlier at `0x5033ac`.
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
- 2026-06-20 archive-family audit: reran the focused matcher and full listing
  while checking the adjacent `load_archive_index` install-store residual. The
  initializer still reports 94.74%, 48/47 candidate/target instructions, and 19
  clean masked operands. The only localized mismatch remains allocator cleanup
  versus controller-cursor materialization (`mov eax, buttons; add esp; sub
  eax, 4` versus native `add esp; mov eax, axis_y`). No archive-index assignment
  owner explained this scheduler choice, so keep the current byte cursor until
  a stronger original-source or layout lead appears.
- 2026-07-11 identical-code-folding correction: the call at `0x430e57` passes
  the base of the tracked-allocation stack at `0x5108c0`, not the subgame
  contact registry. Its one-store initializer is folded with
  `cREnemyManager::Init` at `0x415e20`; the scratch now expresses the call on
  `TrackedAllocationStack` and the reference manifest audits the alternate
  symbol. The focused result remains `94.74%`, `48/47`, with all 19 masked
  operands clean.
- 2026-07-12 cross-port ownership: the exact iOS `RShell.o` symbol is
  `RShellInit()`. Its body owns the same DAT initialization, shell globals,
  registered-sound count, key-repeat state, input slots, scratch allocation,
  and music buffer. The Windows `0x53c7ec` allocation is therefore typed as
  the `RShellScratch` workspace rather than an archive payload address. This is
  codegen-neutral at the retained 94.74% baseline.
- 2026-07-13 controller-owner closure: the reset loop proves two contiguous
  `InputControllerSlot` records beginning at `0x50333c`, with a 0x38-byte
  stride and a one-past end at `0x5033ac`. The shared header now exposes that
  fixed array while retaining the field-address views used by lane-oriented
  helpers. A direct typed-loop spelling makes VC6 choose the `buttons` lane as
  its cursor and regresses to 82.47%; the retained axis-y cursor remains the
  most faithful source shape without inventing dependencies.
- 2026-07-14 allocation-owner closure: `0x5108c0` is now the canonical
  `g_tracked_allocation_stack` object, so the folded initializer is called
  directly on that owner rather than through a cast from its first depth word.
  The focused result remains 94.74%, 48/47, with all 19 operands resolved.
