# set_blend_mode

## 2026-09-11 inline-table certification

The unchanged source now compares at **100%**, 104/104 code
instructions plus 24 bytes of explicitly compared jump-table data. All
16 reference audits are clean and positional. Encoded-body proof is
**exact**.
This is corrected table-data accounting, not newly reconstructed source code.

The [proof report](../../inline-jump-table-proof-20260911.md) and
[receipt](../../inline-jump-table-proof-20260911.json) preserve the full source,
compiled-object identity, data entries, reference audits, comparison ranges, and
encoded-body evidence. Earlier measurements below are historical.

Object blend preset mapper at `0x412d00`. Current result: **100.00%**,
92/92 instructions, prefix 92/92, with all 16 masked operands audited and
clean under the standard `msvc6.5 /O2 /G5 /W3` profile.

The function enables alpha blending and selects source/destination factors
through Direct3D render states `0x1b`, `0x13`, and `0x14`. Its compiler-generated
lookup table at `0x412e30` maps presets `0..20` to six native destinations.
Unrecognized presets leave render state unchanged.

The void contract follows the sole Windows caller, which discards EAX, and
the Android/iOS `G0SetBlend(int)` exports. Windows splits that responsibility
between this object-rendering helper and `set_immediate_blend_mode` at
`0x412e50`.

## 2026-09-07 preset case ownership

The previous 92.39% source manually shared the source/destination suffix with
a `source_blend` local and `goto`. That captured the native control-flow join
but forced the source factor into a register, while native pushes each factor
before entering the shared call suffix.

Ordinary complete preset bodies recover the native sharing when the `0/6`
and `9/12` groups remain separate in source. VC6 independently folds their
identical render-state sequences, while sharing the source-call suffix of
`1/8/20` and `19`. The local and explicit label are no longer needed.

A bounded comparison of source groupings found three forms with identical
function bytes and clean reference audits. The retained `0/6` and `9/12`
partition is a straightforward complete switch, not evidence that the
original source grouping is uniquely determined. Other instruction-exact
forms differed in lookup-table contents and were rejected. Both the lookup
and jump table operands are clean for the retained source.

Primary evidence:

- `analysis/decompile/ida/functions/00412d00-set_blend_mode.c`
- `analysis/decompile/binja/functions/00412d00-set_blend_mode.c`
- `analysis/decompile/android/functions/0008b6f0-_Z10G0SetBlendi.c`
- `analysis/decompile/ios/functions/0006eb94-_Z10G0SetBlendi.c`
