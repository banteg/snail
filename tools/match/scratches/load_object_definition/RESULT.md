# `load_object_definition` match result

## Score

| Metric | Before closure | Final |
|---|---:|---:|
| Match | 55.56% | **100.00%** |
| Target instructions | 316 | 316 |
| Candidate instructions | 314 | **316** |
| Common prefix | 30 / 316 | **316 / 316** |
| Masked operands | 36 clean, 12 mismatched | **59 clean, 0 unresolved, 0 mismatched** |

The exact scratch recovers the `_Object.txt` vertex and facequad parser,
object-owned vertex/facequad allocation, texture-path construction, and
borrowed `TextureRef*` lookup through the global texture manager. The borrowed
`Object*` is a slot from the global `ObjectList`; the loader installs the two
arrays it owns.

Exactness came from recovering three distinct line-advance sites rather than
one unconditional tail call. Non-bracket lines and completed vertex/facequad
sections advance independently, while an unknown bracket marker reaches the
termination test unchanged. VC6 then tail-merges those authentic call sites
into the native control-flow graph, including the out-of-line comment skipper.

There are no instruction or operand residuals.
