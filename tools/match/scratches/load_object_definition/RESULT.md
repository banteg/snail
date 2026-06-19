# `load_object_definition` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **44.80%** |
| Target instructions | 325 | 325 |
| Candidate instructions | 0 | 300 |
| Common prefix | 0 / 325 | **0 / 325** |
| Masked operands | none | **36 clean, 0 unresolved, 5 mismatched** |

This is the first source-shaped scratch for the object definition loader. It
recovers the `_Object.txt` vertex and facequad parser, object-array allocation,
texture path construction, and texture-ref ownership.

## Remaining Work

The next useful improvements are stack-frame/local ownership and preserving the
object pointer in `edi`. After that, revisit the vertex and facequad store
spelling so VC6 emits the native x87 store schedule instead of compact dword
copies.
