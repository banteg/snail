# X2 Format

The shipped `.x2` files are text-based mesh assets with a stripped-down DirectX `.x`-style layout.

Observed structure in representative files:

- `Frame <name> { ... }`
- one or more nested `Material <name> { ... TextureFilename { "foo.tga"; } }` blocks
- `MeshTextureCoords { ... }`
- `Mesh <name> { ... }`
- a per-face material index list at the start of the `Frame` block

Observed quirks:

- files end with a trailing NUL byte
- the final `Mesh` block appears to terminate at EOF rather than with a closing brace in the shipped samples we tested
- animation sequencing is handled separately by `X/_ANIMATION.TXT`, not embedded directly in the `.x2` payloads

## Loader Notes

Verified against the original RWG decompile:

- `TextureFilename` values are resolved to `X/<basename>.tga`
- face material indices are applied after parsing the mesh faces
- faces with four indices are quads and require a fourth vertex read
- faces with other counts are treated as triangles in the original loader
- animation clips are assembled from `.x2` families listed in `X/_ANIMATION.TXT`
- `Duration:` and `Mode:` are used for playback timing
- numbered filename suffixes such as `000`, `001`, and `004` determine keyframe sample positions for interpolation

## Current Port Status

- the Zig runtime already plays these interpolated `.x2` animations directly from the archive
- `Trigger:` lists from `_ANIMATION.TXT` are still under investigation and are not yet applied during playback
