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
