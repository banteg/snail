# cRPath::GetPos @ 0x42b9c0

Exact Windows member: 56/56 instructions with no masked operands. Android and
iOS independently preserve `cRPath::GetPos(tVector&, int, int, tVector&)` and
the same projection.

The method reads `primary_samples[node]`, projects the borrowed local x/y
coordinates through the sample right/up basis, adds the sample origin and
integer row to z, then writes the resulting `tVector`. Both Windows parcel
placement callers discard EAX, proving the void result contract.

Named intermediate vectors reproduce the native VC6 stack and x87 lifetimes;
no aliasing or compiler-coercion construct is retained. The stable matcher
identity remains `get_path_position_at_node`.
