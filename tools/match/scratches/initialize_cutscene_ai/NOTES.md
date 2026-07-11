# initialize_cutscene_ai

Exact `cRCutScene::Init` helper at `0x446130`. The Windows function name stays
stable for the match harness.

The receiver is the exact 0x5c-byte `CutScene` embedded at
`PlayerPresentationController +0x1958` (`Player +0x42dc`). The helper writes
the parent presentation and Player backlinks at `+0/+4` and clears state at
`+0x0c`.

Android exports `cRCutScene::Init`, is called from `cRSubGoldy::Init`, and
performs the same four stores at identical offsets. iOS v1.9 exposes
`cRCutScene::Init(cRSubGoldy*)`; the later build passes the Player explicitly
where Windows and Android recover it from the runtime singleton.

The source return is `void`. Windows happens to leave the presentation pointer
in `eax`, while Android leaves the CutScene receiver in `r0`; callers ignore
both. Those incompatible incidental register values rule out the old integer
return interpretation.

Focused Wibo remains exact: 100.00%, 8/8 instructions, with four clean masked
operands.
