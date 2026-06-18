# destroy_subgame

Exact scratch for the subgame teardown helper at `0x438850`.

Match status: 100% (`246/246` target instructions, `41` masked operands, no
unresolved or mismatched operands).

Recovered behavior:

- emits the stripped `"-SubGame::UnInit()\n"` debug report and marks the
  frontend/subgame bridge dirty byte at `app+0x4f26c`;
- if the level mode is tutorial (`7`), calls
  `TutorialController::uninit_tutorial()` at `game+0xa858`;
- always uninitializes warning, active landscape entries through
  `ActiveLandscapeEntry::clear_active_landscape_entries()`, times-up, and the
  broader subgame BOD pool through `Game::remove_subgame_bods()`;
- for non-state-1 postal/time-trial teardown, flushes row-event display for
  level modes `0` and `1`, then removes active BOD nodes from the 20 SubLazer
  slots, 40 Salt slots, and two ring/special-effect parent slots;
- removes one selected-record BOD node at `game+0xff7bc4` when it is active;
- kills the gameplay HUD widgets at `game+0x35bb88/8c`, clears persistent
  selected-record state, restores frontend state `0x12` for persistent record
  teardown, and sets selected subgame mode `2` when destroying mode `3`;
- in postal mode (`level_mode == 0`), kills the extra two score widgets plus
  the nine lives/widgets starting at `game+0x35bb98`.

The repeated pool loops use a `BodNode::list_next` cursor because native
iterates from the `+0x0c` link field, loading flags from `-0x08` and prev from
`-0x04`. The removal body still mirrors
`BodList::recycle_bod_to_free_list`, but this function inlines it for each
pool and for the selected-record node.
