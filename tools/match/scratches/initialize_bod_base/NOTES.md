# initialize_bod_base @ 0x42f5f0

Exact authored `cRBod::cRBod()` constructor: 27/27 instructions with five
clean masked operands.

Windows initializes the shared BOD vtable, default render/list flags, position,
render arguments, color, object pointer, constructor counter, and remaining
zeroed lifecycle fields in native store order. The inherited `BodNode` prefix
owns the intrusive links and flags; `cRBod` ends exactly at `0x38`.

Android and iOS independently preserve `cRBod::cRBod()` in `RObject.o`, along
with `cRBod::AI()`, `IsAfterSprites()`, `SetObject(cRObject*)`, and
`ApplyPos(tMatrix&)`. The matcher therefore emits constructor syntax and the
exact VC6 symbol `??0cRBod@@QAE@XZ`. Analyzer decompiles may still show the
constructor's receiver in `eax` as a pointer return; that is the low-level
constructor ABI, not a separate receiver-returning method.
