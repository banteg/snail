# initialize_object_list

ObjectList initializer at `0x42f990`.

- Clears the live count and stores the requested capacity.
- Allocates `capacity * sizeof(Object)` bytes under the `"Object List"`
  allocation label.
- Runs `initialize_object` across every backing slot before runtime callers
  start handing out objects with `add_object_to_list`.

2026-07-14 extent ownership: the allocation now derives its 0xdc-byte stride
from the complete shared `Object` type instead of the factored literal
`20 * 11`. Matching remains exact at 30/30 instructions with all three
operands clean.
