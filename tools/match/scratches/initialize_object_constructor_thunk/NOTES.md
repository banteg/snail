# initialize_object_constructor_thunk @ 0x42f6e0

This is the exact Windows `cRObject::cRObject()` constructor, not a descriptive
receiver-returning adapter. Its only operation is a call to the adjacent
`cRObject::Init()` body at `0x42f6f0`; the VC6 constructor ABI then returns the
receiver. The natural constructor definition is exact at 6/6 instructions.

Android independently preserves the same split lifecycle: both constructor
variants call its exported `cRObject::Init()`. iOS preserves the constructor
symbol but inlines the equivalent field initialization. Live Windows xrefs
show one caller in the `cRSubGame` constructor, where VC6 accepts the direct
subobject spelling `face->movie.cRObject::cRObject()` without the null guard
introduced by placement-new. The old fake member aliases are therefore gone.

The function lies inside the verified contiguous `RObject.o` run between
`cRBod::ApplyPos` and `cRObject::Init`.
