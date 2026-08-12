# RTextExtractFloat

Exact at 64/64 instructions with nine clean relocation masks. The source scans
to a sign, dot, or digit, accumulates decimal digits and scale in float32, and
advances the caller-owned cursor. Its loop order preserves the native range
checks and x87 temporary lifetimes without code-generation coercion.

Android and iOS retain two code-equivalent bodies: `RTextExtractFloat(char**)`
in `RShell.o` and a later `Rstrfloat(char**)` in `RString.o`. Windows places
this body immediately after `RTextExtractInt`, completing the same seven-entry
RText sequence, while mobile `ObjectTextLoad` calls the RText entry at the same
vertex and face fields as Windows `load_object_definition`. Sequence and
call-graph evidence therefore resolve the canonical owner as
`RTextExtractFloat` rather than the duplicate sibling.
