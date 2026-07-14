# release_direct3d_device_interfaces @ 0x411960

Owns teardown of the two Direct3D COM interfaces stored by
`Direct3DRenderer`:

- `device` at `+0xbb94` is released first and cleared;
- the `Direct3D8` interface at `+0xbb90` is then released and cleared.

Native calls vtable slot `+0x08` for both objects, the COM `Release` slot. The
shared `Direct3DDevice8Vtbl` and `Direct3D8Vtbl` now expose that inherited COM
slot directly, so teardown no longer recasts either owned interface into a
scratch-local release-only shell. The exact teardown remains the regression
oracle for the shared ABI; the repository-wide exact audit covers all other
consumers of both vtables.
