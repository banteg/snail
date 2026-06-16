# is_bod_after_sprites

Tiny render-order helper at `0x42f5c0`.

Current Wibo result: 100.00%, 3/3 instructions, no masked operands.

The function tests the low byte of `BodBase::flags` for bit `0x80` and returns
the result in `al`, so the source signature is `bool` rather than `int`. This
gives the render-frame split a shared name: BODs with bit `0x80` are rendered in
the post-sprite pass, while the others are rendered before sprite depth output.

Source-shape detail: VC6 emits the native `test byte [ecx+4], 0x80; setne al`
for an explicit `if ((flags & 0x80) != 0) return true; return false;` branch.
The shorter boolean expression compiles to a shift/and sequence instead.
