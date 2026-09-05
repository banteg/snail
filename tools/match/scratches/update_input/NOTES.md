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
