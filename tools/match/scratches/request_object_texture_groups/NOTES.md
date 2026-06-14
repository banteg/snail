# request_object_texture_groups @ 0x42f930

Near-exact match at 96.55%.

Semantics:

- first request allocates `requested_count * 4` bytes for facequad texture
  groups at `+0x6c`;
- records live count at `+0x64` and fixed capacity at `+0x68`;
- later requests reuse the fixed buffer and report
  `"Fixed FaceQuadTextureGroupsNumber too small"` if the requested live count
  exceeds capacity;
- every request updates the live count at `+0x64`.

Residual:

- the existing-allocation branch has a one-instruction load-order difference:
  the target loads the requested count before `texture_group_capacity`, while
  the current source loads capacity first. Natural `>`, `<=`, preloaded
  `result`, and separate `count`/`capacity` spellings all keep the same
  residual, so this is pinned unless a stronger VC6 source-idiom lead appears.
