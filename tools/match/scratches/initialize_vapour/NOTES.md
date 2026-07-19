# initialize_vapour

Exact 100.00% Windows match: 19/19 instructions with three clean masked
operands. This is the void `cRVapour::Init(cRObject*, float)` member preserved
by Android and iOS.

The explicit `Object*` argument is unused in both Windows and Android. The
method reads the retained `Object*` at `Vapour +0x24`, derives capacity from
`Object::facequad_count + 1`, stores the half-width, allocates the 0x40-byte
transform history, and tail-dispatches `reset_vapour`. Android establishes no
result before that tail call, confirming the void source contract.

## 2026-07-17 RenderableBod inheritance closure

The two exact JetPack child-construction calls initialize the complete
zero-offset `RenderableBod` prefix before installing the cRVapour callback
table. `Vapour +0x24` is therefore the inherited `BodBase::object`, not a
parallel trail-specific owner field. The exact 0x94-byte extent and this
initializer's 19/19 machine-code match are unchanged.

## 2026-07-19 analysis-lane base composition

The narrow Binary Ninja header now mirrors the same complete zero-offset
`RenderableBod body` as the broad header and matcher. Removing its synthetic
`Object* owner` prevents broad/narrow replay order from changing the type;
the retained pointer still resolves honestly as `body.bod.object` at `+0x24`.
The exact 19/19 matcher body is unchanged.
