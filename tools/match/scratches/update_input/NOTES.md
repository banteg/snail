# update_input @ 0x40aa80

Verified Android owner and semantics: `cRInput::Update()` derives pressed and
released edges, advances the previous mask, stores the inverse current mask,
and clears the current word. The exact Windows `cRGameInput::AI()` caller
ignores EAX, proving the member is void.

The honest Windows source remains 52.94%, 15/19 instructions, with no masked
references. Native alone saves EDI for the released-mask tail. Three recorded
sweeps cover 192 ordinary statement-order, signedness, and temporary-lifetime
variants: 17 are byte-identical and 175 regress. That history bounds the known
compiler residual but is not a stopping rule; the descriptive matcher name
remains until a new evidence-backed source relationship reproduces it.
