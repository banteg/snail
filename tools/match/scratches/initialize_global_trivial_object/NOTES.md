# initialize_global_trivial_object

CRT constructor body at `0x406d20` for the 16-byte global at `0x4df848`. It
passes that owner to the folded three-byte no-op constructor at `0x44db50`.
The next global begins at `0x4df858`, fixing the extent, but no other instruction
addresses the object and the folded constructor is shared by several classes;
the original class therefore remains deliberately generic.
The generic owner call matches the native 2/2 instructions exactly, with both
masked operands resolved.
