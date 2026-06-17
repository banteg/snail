# set_snail_jetpack @ 0x445860

First tracked scratch for the jetpack presentation dispatcher. The important
struct correction is that this is also a `PlayerPresentationController` method:
the known callers pass `g_game_base + 0x432700`, which is `Player +0x2984`, not
a separate global presentation controller.

Recovered behavior:

- input state `0` maps to channel state `0`;
- input state `1` maps to channel state `4`;
- any other input is passed through as the target state;
- leaving selected state `4` queues animation `1` with frame `8` and plays
  sound `26`;
- entering target state `4` plays animation `1`, queues animation `0`, plays
  sound `16`, and stores selected state `4`;
- entering target state `0` clears the channel with animation `-1`.

Focused Wibo result: 54.55%, 59/62 candidate/target instructions. The switch
spelling for the input-state mapping is better than the direct `if` ladder
(50.00%); the remaining drift is register ownership. Native loads `state`
before saving registers, keeps `this` in `edi`, keeps `target_state` in `ebx`,
and only saves `esi` around the enter-state-4 block. The current source keeps
`this` in `esi` and `target_state` in `edi`, then constant-folds the selected
state store in the state-4 return path. Keep this as a clean relationship
scratch unless a real VC6 source idiom explains that register split.
