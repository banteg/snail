# `load_object_definition` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **48.23%** |
| Target instructions | 325 | 325 |
| Candidate instructions | 0 | 297 |
| Common prefix | 0 / 325 | **2 / 325** |
| Masked operands | none | **36 clean, 0 unresolved, 5 mismatched** |

This source-shaped scratch for the object definition loader now also shares the
global `ObjectList -> Object` ownership model. It
recovers the `_Object.txt` vertex and facequad parser, object-array allocation,
texture path construction, and texture-ref ownership.

## Remaining Work

The native `0x23c` frame is recovered. The next useful improvement is early
callee-saved register ownership: native saves `ebp` before `esi` and preserves
the object pointer in `edi`. After that, revisit the vertex and facequad store
spelling so VC6 emits the native x87 store schedule instead of compact dword
copies.
