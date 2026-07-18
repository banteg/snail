# is_bod_after_sprites

Tiny render-order helper at `0x42f5c0`.

Current Wibo result: 100.00%, 3/3 instructions, no masked operands.

The function tests the low byte of inherited `BodNode::list_flags` for
`BOD_FLAG_AFTER_SPRITES` (`0x80`) and returns the result in `al`, so the source
signature is `bool` rather
than `int`. This gives the render-frame split a shared name: BODs with bit
`0x80` are rendered in the post-sprite pass, while the others are rendered
before sprite depth output.

Source-shape detail: VC6 emits the native `test byte [ecx+4], 0x80; setne al`
for an explicit `if ((list_flags & 0x80) != 0) return true; return false;`
branch when `list_flags` is signed. With the earlier unsigned contact flag
type, VC6 compiled this same source to a shift sequence, so the helper also
pins the shared flag word as signed.

## 2026-07-18 analyzer ownership replay

The analyzer method now keeps its native `bool` result and a `BodBase*`
receiver, exposing the inherited `BodNode::list_flags` owner to the two-pass
renderer instead of retaining the raw `this + 4` expression.
