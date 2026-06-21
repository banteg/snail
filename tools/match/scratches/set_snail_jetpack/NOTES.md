# set_snail_jetpack @ 0x445860

First tracked scratch for the jetpack presentation dispatcher. The important
struct correction is that this is also a `PlayerPresentationController` method:
the known callers pass `g_game_base + 0x432700`, which is `Player +0x2984`, not
a separate global presentation controller.

The scratch now uses the shared `player.h` controller layout directly; the
older local `+0x11e0` controller view has been removed.

Recovered behavior:

- input state `0` maps to channel state `0`;
- input state `1` maps to channel state `4`;
- any other input is passed through as the target state;
- leaving selected state `4` queues animation `1` with frame `8` and plays
  sound `26`;
- entering target state `4` plays animation `1`, queues animation `0`, plays
  sound `16`, and stores selected state `4`;
- entering target state `0` clears the channel with animation `-1`.

Focused Wibo result after the shared selected-state tail: 86.18%, 61/62
candidate/target instructions. The switch spelling for the input-state mapping
is still better than the direct `if` ladder, while sharing the final
`selected_state = target_state` store across the enter-state-4 and clear paths
removes the old constant-folded state-4 return tail.

The remaining drift is register ownership. Native loads `state` before saving
registers, keeps `this` in `edi`, keeps `target_state` in `ebx`, and only saves
`esi` around the enter-state-4 block. The retained source still saves `ebx`
before loading `state`, but now preserves the native shared tail shape. Tested
variants: initializing `target_state = state` recovers the first argument load
but regresses to 66.67% by losing the better switch/register split; flattening
the tail as `if target == 4 else if target == 0` reaches 82.93%; checking the
clear path first regresses to 71.54%. Keep the nested shared-store tail unless
a real VC6 source idiom explains the remaining prologue split.
