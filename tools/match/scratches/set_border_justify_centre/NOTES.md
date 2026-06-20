# set_border_justify_centre

Small border/runtime mutator at 0x404730. Both BN and IDA decompiles show it
storing the argument at this+0x435b0 and returning the same value.

Exact match: 100.00%, 3/3 instructions, no masked operands.

Shared in `border_runtime.h` for the menu/background callers that only need the
trailing justify field. Do not fold this into `BorderManager` casually:
`allocate_border` is still modeled as returning `BorderRecord*` in the concrete
manager header, while several front-end scratches use local allocator views that
return `FrontendWidget*`; that relationship needs its own evidence pass.
