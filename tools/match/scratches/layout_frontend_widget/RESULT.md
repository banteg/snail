# Exact frontend widget layout

`cRBorder::RePosition()` at `0x4024a0` matches **177/177 native
instructions**, the complete prefix, and **20 clean references**, using
`msvc6.5 /O2 /G5 /W3`.

The final source restores the recursive value-widget call and accesses the
receiver's layout fields directly. VC6 performs tail-recursion elimination
and produces the native mutable receiver loop itself. Together these source
choices resolve the final load-order difference from the 99.44% baseline.
Hit-position publication now uses ordinary float assignments, and the redundant
clamped-top copy is removed. The native-supported sprite bit-copy pair remains.

The body still selects sprite, authored rectangle, or measured text geometry,
clamps the hit coordinates, updates anchors and slider bounds, and lays out
all three slider children. No ownership layout, ABI, compiler option, shared
helper, or reference-audit rule changed.

The dated notes and mutation receipts preserve the earlier partial results,
the corrected recursive combinations, and the final exact simplification.
