# cRBackdrop::Init @ 0x410e20

Exact Windows member: 55/55 instructions with all four masked operands clean.
The unstripped Android build independently preserves `cRBackdrop::Init(int)`;
there is no verified iOS body.

The sole Windows caller passes mode `1` to the `cRBackdrop` embedded at
`GameRoot +0x4ec10`. Init establishes the render gate and transition rates,
initializes the two 0x20-byte `BackdropWorldBlend` lanes, selects world zero,
and clears distortion. Native retains distinct mode 0, mode 1, and fallback
paths, so the exact two-case `switch` remains source-significant.

Android proves the shared tail layout from the render gate through both world
blend lanes. Its corresponding buffer member is an element-buffer handle for
the four grid-corner indices; the adjacent click-start byte remains unnamed
because no reader proves a stronger role.
