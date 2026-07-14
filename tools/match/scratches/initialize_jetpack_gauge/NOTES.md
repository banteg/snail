# initialize_jetpack_gauge

Exact at `100.00%`, `15/15`, with three clean masked operands.

2026-07-11 ownership closure: the controller borrows the `SubgameRuntime`
embedded at `GameRoot +0x74618` and that runtime's owned `Player` at
`+0x3bb764`. Replacing byte pointers with those real owners is codegen-neutral.

Cross-port Android identifies the exact field/store body as
`cRSubHover::Init(int)`; iOS v1.9 exposes `cRSubHover::Init(cRSubGoldy*)`.
The normalized exact 0x214-byte owner is `SubHover`, with borrowed Player and
SubgameRuntime backlinks at `+0x10/+0x200`. Its authored return is void; the
honest void definition remains exact at 15/15 instructions.

## 2026-07-14 hover lifecycle ownership

Initialization now seeds `SUB_HOVER_STATE_INACTIVE`. Live Windows field xrefs
and Android `cRSubHover::{Init,On,AI,End}` agree that `+0x0c` is the exact
two-state lifecycle owner. Focused output remains exact at 15/15 instructions
with all three operands clean.
