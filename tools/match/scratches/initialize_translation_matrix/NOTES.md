# initialize_translation_matrix

First tracked scratch for `initialize_translation_matrix @ 0x44fd90`.

The helper is a stdcall matrix initializer with four parameters:

- output `TransformMatrix*`;
- translation `x`, `y`, and `z`.

It writes the translation into slots `+0x30/+0x34/+0x38`, clears the remaining
non-diagonal lanes, sets the diagonal lanes to `1.0`, and returns the output
matrix pointer.

`scratch.conf` pins `END=0x44fdec` because the curated manifest gap runs to the
next late math helper and overstates this function's byte size.

The current scratch uses the shared `TransformMatrix` layout and a float-slot
view to preserve the source write order. The residual is codegen only: the
native helper stores zero and one via `fldz`/`fld1` plus `fstp`, while VC6.5
under the normal scratch flags folds the same float constants into integer
stores. Trials with `/Op`, C mode, no `/O2`, double literals, and long-double
literals did not recover the x87 constant-store form.

2026-07-03 provenance identification: this is `D3DXMatrixTranslation` from the
DirectX 8 SDK's D3DX8 static library, not game code. The signature matches
exactly (stdcall `(pOut, x, y, z)`, returns `pOut`, translation into
m[12..14], identity elsewhere), and the `fldz`/`fld1` x87 constant stores are
the VC7 build-9178 idiom named in the Rich-header provenance. Per the project
toolchain rule ("link the original libs, never decompile these"), this scratch
is a semantic reference only and is expected to stay unmatched under msvc6.5.
