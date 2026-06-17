# initialize_completion_screen

`initialize_completion_screen` @ `0x404920` builds the delivery-complete result
screen object used by the cutscene completion handoff. It is called only from
`update_cutscene` with `game+0x12e6df0`, not from the frontend prompt object at
`game+0x4f3ac`.

Recovered relationships:

- `CompletionResultScreen` uses widgets at `+0x00/+0x04/+0x08/+0x0c/+0x10`.
- `+0x48` is the computed bonus score and `+0x4c` is the total score built from
  `game+0x430060 + delivered_count * 100 + bonus`.
- Postal perfect delivery awards `50,000`; challenge mode indexes the two
  `0x4a1194/0x4a11ac` six-entry bonus tables from either live challenge slider
  globals `data_4df960/4df958` or replay record fields `+0x50/+0x4c`.
- The `HighScoreRecord` tail fields at `+0x48/+0x4c/+0x50` now line up with the
  `complete_subgame` result-record copy and the completion replay bonus read.

Current match: 64.10%, 278 target instructions / 268 candidate instructions,
34 masked operands all resolved. The main residual is source-shape scheduling:
native loads `g_game_base` before allocating the `Color4f` stack local and keeps
the y/x bonus indices in `esi/edx`, while the scratch's straightforward C++
keeps the game pointer in `edi` and swaps some index registers. No fakematching.
