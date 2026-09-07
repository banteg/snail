# update_input @ 0x40aa80

Verified Android owner and semantics: `cRInput::Update()` derives pressed and
released edges, advances the previous mask, stores the inverse current mask,
and clears the current word. The exact Windows `cRGameInput::AI()` caller
ignores EAX, proving the member is void.

The honest Windows source remains 52.94%, 15/19 instructions, with no masked
references. Native alone saves EDI for the released-mask tail. The authored
owner and method name are independent of that compiler register-allocation
residual, so the source and COFF symbol retain `cRInput::Update()` without
claiming an exact instruction match.

## 2026-09-05 goal-600 source ownership campaign

The earlier claim that an ignored Windows return proves a void method is too strong. An unused result alone cannot establish the return contract. Independently locating `_ZN7cRInput6UpdateEv` in both Android ELF symbol tables finds the armeabi body at 0x3188c (56 bytes) and armeabi-v7a body at 0x2e060 (52 bytes). Both retain R0 as the receiver throughout and leave it unchanged, rather than returning the button mask preserved in Windows EAX. That cross-port evidence supports retaining the shared void declaration; no result API is introduced to force the Windows register schedule.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-07 edge publication and current-mask lifetime

Recovered exactly under the unchanged `msvc6.5 /O2 /G5 /W3` profile:
**100%, 19/19 instructions, prefix 19**, with no masked reference operands.
The native body preserves the current mask while deriving separate pressed,
released, and inverse values. Publishing the two edge masks before advancing
`previous_buttons` recovers its saved EDI and the complete native schedule.
The old source advanced the previous state first and reused the current local
for its inverse, allowing VC6 to collapse those lifetimes.

`edge-publication-order-20260907.json` compares 240 statement-order and
local-ownership forms. Six are exact; the retained form names each derived
mask and finishes by clearing `current_buttons`. All formulas, field types,
and the independently supported void ABI are unchanged. This resolves the
former register-allocation residual through ordinary source data flow.
