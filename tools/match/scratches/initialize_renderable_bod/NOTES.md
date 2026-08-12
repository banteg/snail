# initialize_renderable_bod @ 0x42f650

Exact authored `cRBodPos::cRBodPos()` constructor: 10/10 instructions with
three clean masked operands.

Windows invokes `cRBod::cRBod()`, installs the positioned-body vtable and
transform render flag, and constructs the embedded `tMatrix` at `+0x38`.
`cRBodPos` ends exactly at `0x80`; its final two lanes remain untouched here.

Android and iOS independently preserve `cRBodPos::cRBodPos()` in `RObject.o`
and the same inherited `cRBod::AI()` vtable entry. The matcher emits constructor
syntax and the exact VC6 symbol `??0cRBodPos@@QAE@XZ`. A pointer return in the
tracked C-style analyzer replay is only the native constructor ABI view.
