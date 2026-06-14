# initialize_quaternion_from_axis @ 0x44d530

Near-exact match: 77.78%, 26/26 instructions.

Builds a quaternion from an axis-angle record by calling the exact sine/cosine
table helpers with `angle * 0.5f`, scaling xyz by sine, and storing w from
cosine.

Residual: the call setup now matches native, but VC6 emits the scale
multiplications as `fld axis; fmul st(1)` plus a final `fstp st(0)` while native
duplicates the live sine result with `fld st(0)` before multiplying each axis
component. This is x87 operand-order/scratch-stack scheduling only.
