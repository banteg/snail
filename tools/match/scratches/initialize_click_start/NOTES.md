# initialize_click_start

`initialize_click_start` @ `0x442170` seeds the subgame "Click to Start"
owner. It allocates the prompt widget, links the owner into the active BOD
list, resets the player-side startup/replay index at `Player+0x304`, and hides
the prompt immediately when the app replay-launch scratch is active.

Match status: 100.00%, 79/79 target instructions, 13 masked operands all
resolved. No fakematching.

Recovered relationships:

- the owner is a `RenderableBod` subclass; `update_click_start` later moves the
  embedded transform at `+0x38`;
- active-list flags reuse the shared BOD semantics: `0x200` linked,
  `0x40` iterator guard;
- `Player+0x304` is kept as a local click-start view for now because
  `update_subgoldy` also uses it as a replay/ghost anchor cursor.

Source-shape note: the active-list insertion wants the same native-looking
pointer reload idiom as nearby BOD owners, including the temporary
`current->list_prev` readback before assigning the list head.
