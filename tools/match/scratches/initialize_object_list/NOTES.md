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

## 2026-07-18 global lifecycle replay

The sole initializer call passes `&g_object_list` with capacity 3000 and
discards `eax`, confirming the exact `void ObjectList::initialize_object_list`
contract rather than treating the final constructed slot as a returned owner.
Both analyzer replays now bind the 0x0c-byte global container at `0x4b7648`,
width-gate its count/capacity/backing-pointer layout, and reanalyze the full
allocator consumer set. The initializer remains exact at 30/30 instructions.

## 2026-07-23 backing-array lifetime replay

The guarded ObjectList replay now preserves the allocation and construction
walk in Binary Ninja. `ObjectList::objects` is the owned `Object*` allocation;
each completed address is a borrowed `Object*`, while the native 0xdc traversal
state remains an integer `object_byte_offset` rather than a fake pointer. The
replay verifies `sizeof(ObjectList) == 0x0c`, `sizeof(Object) == 0xdc`, and the
count/capacity/objects layout before mutation, then saves and reads back every
annotation. A second replay is fully idempotent.

The exact matcher source remains unchanged at 100.00%, 30/30 instructions,
prefix 30/30, with three clean masked operands.

## 2026-07-29 authored owner closure

Android and iOS retain the manager as `cRObjects` and its slots as
`cRObject`. Those names are now primary in the matcher; `ObjectList` and
`Object` remain compatibility typedefs for the analyzer replay and partial
callers. The exact Windows void initializer shape is unchanged.
