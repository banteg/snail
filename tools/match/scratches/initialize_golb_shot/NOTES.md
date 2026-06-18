# Exact match

`initialize_golb_shot` @ 0x408690 constructs one 0x2e8-byte Golb shot slot.
`initialize_runtime_pools_and_path_template_bank` seeds 12 of these slots, and
`update_movement_flag_emitters` later iterates that same 12-slot bank before
calling `create_golb`.

The callback tables pin the ownership:

- `data_49734c` starts at `update_golb_ai`;
- `data_49731c` starts at `update_vapour`, so the old
  `g_track_jetpack_body_vtable` name was too narrow;
- `data_497350` starts at `noop_runtime_ai` for the tertiary embedded body.
