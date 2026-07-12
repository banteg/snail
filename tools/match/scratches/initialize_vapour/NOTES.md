# initialize_vapour

Exact 100.00% Windows match: 19/19 instructions with three clean masked
operands. This is the void `cRVapour::Init(cRObject*, float)` member preserved
by Android and iOS.

The explicit `Object*` argument is unused in both Windows and Android. The
method reads the retained `Object*` at `Vapour +0x24`, derives capacity from
`Object::facequad_count + 1`, stores the half-width, allocates the 0x40-byte
transform history, and tail-dispatches `reset_vapour`. Android establishes no
result before that tail call, confirming the void source contract.
