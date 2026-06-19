# initialize_backdrop_tile_quad reconstruction notes

`initialize_backdrop_tile_quad` builds one oriented textured backdrop tile quad.
It requests four vertices and one facequad, assigns the fixed tile UV window,
rotates that UV window according to the orientation, writes the oriented
quad-local X/Z coordinates, then applies an edge-selector pass over all four
vertices.

Important type notes:

- The function is a cdecl helper:
  `void initialize_backdrop_tile_quad(Object*, int edge_selector, int orientation,
  int row_selector, int column_selector, char* texture_path)`.
- Binary Ninja's apparent float return is stale x87/register state; the caller
  discards it and fixes the stack by `0x18`.
- `sub_430a30` is a fastcall/thiscall-shaped helper over `ObjectFaceQuad` that
  rotates the four UV pairs.

Current focused result:

- match: 79.32%
- target/candidate instructions: 367 / 339
- prefix: 91 / 367
- masked operands: 51 clean, 7 unresolved, 0 mismatched

Remaining gap:

The scratch matches the setup prefix and preserves the orientation/edge-selector
structure, but it is still a high mid-progress reconstruction. The unresolved
masked operands are the two generated jump tables plus the six calls to the
local UV-rotation helper symbol. The main code-shape differences are register
choice for the negative X/Z constants in the orientation cases and shorter
edge-selector blocks where MSVC still simplifies some repeated sign tests.
