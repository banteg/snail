# release_direct3d_device_interfaces @ 0x411960

Owns teardown of the two Direct3D COM interfaces stored by
`Direct3DRenderer`:

- `device` at `+0xbb94` is released first and cleared;
- the `Direct3D8` interface at `+0xbb90` is then released and cleared.

Native calls vtable slot `+0x08` for both objects, the COM `Release` slot. The
scratch keeps narrow release-only views for both interfaces so exposing one
additional vtable member does not perturb compiler-local label numbering in
unrelated exact scratches that consume the broad shared device view.
