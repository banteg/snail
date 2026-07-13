# `load_png_image` reconstruction notes

## Ownership and ABI

`load_png_image @ 0x42f0a0` is a real authored helper, not part of the preceding
Cage2 path constructor. Its `ret` is at `0x42f464`, giving a 965-byte function
with seven ordinary cdecl arguments. The sole caller is
`rebuild_game_archive_if_needed`, which supplies a temporary `0.png` path,
pixel/dimension/channel outputs, a three-byte background-color output, and a
zero file offset.

The apparent extra live `esi` and `edi` arguments in older decompiler output are
setjmp data-flow artifacts. Direct stack reads stop at `[ebp+0x20]`.

## Recovered source shape

The helper is a thin libpng 1.2.5 compatibility loader. It:

- optionally seeks to an embedded-file offset;
- validates the eight-byte signature through legacy `png_check_sig`;
- creates libpng read/info state in two file-scope scratch pointers;
- installs the VC6 setjmp recovery point;
- expands palette, low-bit-depth, transparency, and grayscale inputs into the
  RGB/RGBA byte layout consumed by the archive-to-TGA converter;
- applies a PNG bKGD color and optional gAMA correction;
- allocates a contiguous pixel buffer plus a temporary row-pointer table; and
- reads the image, frees the row table, closes the stream, and returns success.

The two globals at `0x5032f4` and `0x5032f8` are owned only by this loader. They
are libpng scratch state for the legacy archive rebuild path, not persistent
gameplay objects.

## Third-party boundary

The direct callees from `0x461c31` and `0x47d900` through `0x482f3e` are
statically linked libpng 1.2.5 APIs. Naming those calls distinguishes authored
loader control flow from bundled library implementation without promoting the
library internals as gameplay functions.

## Matching policy

The scratch expresses the recovered loader semantics directly. The `setjmp`
call uses the VC6 macro expansion used by libpng; there is no inline assembly,
artificial padding, dummy control flow, or fabricated global access.

The authentic VC6 `<setjmp.h>` macro and the jump buffer at the beginning of
`png_struct_def` recover the compiler-mandated EBP frame. With that source
contract restored, the scratch is exact: 371/371 instructions, a full common
prefix, and 78 clean masked operands.
