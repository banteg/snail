Best current result: 89.13%.

The native stack has two `Vector3` locals: the camera-minus-player delta is
stored at `esp+0xc..0x14`, copied to `esp+0x18..0x20`, and the copy is passed to
`normalize_vector`. Modeling that as `normalized_vector = vector` matches the
full stack/vector-copy region and raises the scratch from 80.90%.

Remaining miss: after clamping the attachment-exit volume below zero, the target
stores `0.0f` and jumps to the shared `play_sound_effect_scaled` tail. VC6.5
continues to duplicate that call tail in source-equivalent forms tried so far:
structured `else if`, two independent `if`s, explicit `goto play_scaled`,
nested `else`, ternary clamp, do/break clamp, sentinel-initialized `sound_id`,
and a raw-double lower-bound spelling. Avoid using volatile, fake symbols, or
asm to force this tail merge.

2026-06-13 pin audit: focused matcher still verifies 89.13%, 96/88 insns.
Semantics are pinned: movement flag buckets, RNG variant draws,
camera-minus-player vector staging, normalized distance volume, and both audio
call paths match the recovered behavior. Leave the remaining residual as
clamp-tail control-flow duplication unless a new source-shaped VC6 tail form
appears.

2026-06-20 larger motion-audio retry: focused Wibo still reports 89.13%,
96/88 candidate/target instructions, 26/88 prefix, and 19 clean masked
operands. The addressed dump confirms native stores zero for the lower clamp
then jumps to the shared `play_sound_effect_scaled` tail. Inverting the source
guard to `if (volume >= 0.0f) ... else ...` regresses to 88.04% by duplicating
the upper clamp tail instead. Two independent clamp guards are codegen-neutral
and still duplicate the lower tail. The exact `play_sound_effect_scaled`
scratch and shared audio header keep the callee `void`, so changing the ABI
would be source-false. No canned `snail match idioms` clamp case exists; keep
the clearer `if/else if` clamp until a real VC6 tail-merge source idiom is
identified.

2026-07-14 camera owner closure: root `+0x18c..+0x194` is
`GameRoot::players[0].transform.position`, the inherited renderable transform
of the front-end `GamePlayer`. The attachment-exit volume therefore measures
from that camera/player presentation position to the gameplay Goldy position.
Naming the aggregate owner is codegen-neutral at the retained 89.13% baseline.

## 2026-07-16 void helper ABI

Both direct `update_subgoldy` callsites discard EAX. The two native returns
either follow `play_sound_effect_scaled` or `play_sound_effect`, so the observed
register value is merely the callee's incidental residue; the early no-sound
path likewise promises no result. BN and IDA now preserve the source-authored
`void __thiscall(Player*)` contract. The matching source already used that ABI
and remains unchanged at 89.13%, 96/88 instructions, prefix 26/88, with all 19
masked operands clean.
