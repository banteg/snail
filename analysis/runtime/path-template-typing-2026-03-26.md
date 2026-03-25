## Path-Template Typing Pass

Date: March 26, 2026

### Summary

The repeated Windows decompile pattern

```c
*(float *)(*(_DWORD *)(this + 88) + v8 + 144)
```

is not a vtable access.

It is a field load from one of the two sampled-point arrays owned by the path-template record:

- `this + 0x58` / `this + 88`: `primary_samples`
- `this + 0x5c` / `this + 92`: `secondary_samples`

After the Binary Ninja type update, the same expression reads as:

```c
*(&self->primary_samples->center_x + i)
```

That is still imperfect HLIL, but it is structurally the right object model:

- `self` is a `PathTemplate*`
- `primary_samples` is a `PathTemplateSample*`
- the sample stride is `0xa8`
- offset `+0x90` inside one sample is the current `center_x` field

### Record Shapes

Recovered Windows `PathTemplate` fields that matter for the constructor/follow path:

- `+0x38`: `kind`
- `+0x3c`: `is_mirrored_x`
- `+0x40`: `side_exit_mode`
- `+0x44`: `segment_count`
- `+0x4c`: `segment_count_f`
- `+0x54`: `width_cells`
- `+0x58`: `primary_samples`
- `+0x5c`: `secondary_samples`
- `+0x98`: `installed_heading_delta`
- `+0x9c`: unresolved special runtime flag

Recovered `PathTemplateSample` shape:

- size: `0xa8`
- `+0x00..+0x2f`: three `0x10`-byte matrix rows
- `+0x30`: `position`
- `+0x80`: `delta_dir_to_next`
- `+0x8c`: `delta_length`
- `+0x90`: `center_x`
- `+0x94`: `rotation_scalar_94`
- `+0x98`: `rotation_scalar_98`
- `+0x9c`: `lateral_scale`
- `+0xa0`: `special_scalar`

Important correction:

- the first `0x30` bytes are not three packed `Vec3`s
- they behave like a `3x4` matrix block with row starts at `+0x00`, `+0x10`, and `+0x20`
- that is why the decompile kept bouncing between `+0x10`, `+0x20`, and `+0x30`

### Cross-Port Check

Android `cRPath::BuildHalfPipe` independently matches the same shape:

- builder object stores count/width fields before node allocation
- `GetNodes()` seeds two sample-array pointers
- both arrays use the same `0xa8` sample stride
- the constructor writes per-sample values at `+0x90`, `+0x94`, `+0x98`, `+0x9c`, `+0xa0`
- later passes compute `delta_dir_to_next` and `delta_length` from `position`

So the ugly Windows pointer arithmetic is best understood as:

- struct field access into a sampled-point array
- not a virtual dispatch table
- not an array of function pointers

### Binary Ninja Updates

Applied in the live BN database:

- `PathTemplate`
- `PathTemplateSample`
- `allocate_path_nodes(PathTemplate* self)`
- `finalize_path_template_record(PathTemplate* self)`
- `initialize_kind42_path_template_pair(PathTemplate* self, ...)`
- `initialize_halfpipe_path_template_pair(PathTemplate* self, ...)`

One caution remains:

- the `thiscall` stack argument names on `initialize_kind42_path_template_pair` are still presentation-noisy in BN
- keep the field model and array layout; do not over-trust the pretty parameter names there yet
