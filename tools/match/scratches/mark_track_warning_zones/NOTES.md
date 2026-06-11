# WIP — 32.51%, register allocation diverges

Control flow, constants, and operations all line up in the diff; our
build moves `this` out of ecx and spills differently, so the score is
low despite structural agreement. Needs more layout iteration if a full
match is ever wanted; the semantics below are already pinned by the asm
read and are what blind spot #6 needs:

- seed tile set: {2..14, 23, 25, 33} (literal 16-way compare chain)
- stamp footprint per seed at (row, col): rows row..row-5, cols
  {col-1, col}, bounds-checked `r >= 0 && r < rows-1 && 0 <= col+dc < 8`
  as signed pairs
- effect: `cells[idx].flags |= 0x18`
- cell bank: game + 0x3bfb04, stride 84 (0x54), tile byte +0x00,
  flags dword +0x04, 8 cells per row, row-major contiguous walk
