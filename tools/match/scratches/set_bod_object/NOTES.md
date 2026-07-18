# set_bod_object @ 0x42f5d0

Exact match: 100.00%, 6/6 instructions.

The method stores a borrowed `Object*` at `BodBase +0x24`, raises the shared
`BOD_FLAG_HAS_OBJECT` bit in the inherited `BodNode::list_flags`, and returns
the updated flag word. iOS names the same owner boundary
`cRBod::SetObject(cRObject*)`; every recovered Windows caller supplies either
an object-list allocation, another BOD's object, or null.

The Binary Ninja replay now uses the same `BodBase*` receiver and `Object*`
argument. This removes the former `void*`/integer ABI and lets callers retain
their render-object ownership across the attachment call.

## 2026-07-18 paired analyzer replay

The same `int32_t __thiscall(BodBase*, Object*)` contract is now durable in IDA
as well as Binary Ninja. The return remains the updated flag word; it is not
coerced to `void` merely because most attachment callers ignore it.
