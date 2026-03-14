# Android -> Windows Symbol Matches (Sweep 5)

Fifth cross-reference pass covering: the gameplay-camera helper family from bundle 12/13, the tip-slot helpers behind `cRTipManager`, and a small click-start bookkeeping follow-up.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN, `EXISTS` = already named, `IMPLIED` = not part of the original bundle-12 unresolved list, but now strongly implied by the Android call graph

---

## Camera Controller Confirmation

These were already functionally identified on Windows, but the Android ELF confirms the original class ownership directly:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRCameraman::Init` | 0x446160 | `initialize_cameraman` | -- | EXISTS |
| `cRCameraman::AI` | 0x4461d0 | `update_cameraman` | -- | EXISTS |
| `cRSubGame::CameraAI` | 0x446020 | `update_subgame_camera` | -- | EXISTS |
| `cRTutorial::Init` | 0x448da0 | `initialize_tutorial` | -- | EXISTS |
| `cRTutorial::AI` | 0x448de0 | `update_tutorial` | -- | EXISTS |
| `cRTutorial::UnInit` | 0x448dd0 | `uninit_tutorial` | -- | EXISTS |

---

## cRTip / cRTipManager

Android exposes both `cRTip` and a separate older `cRToolTip` system. The bundle-12 helpers behind `enqueue_tip_message` and `update_tip_manager` match `cRTip`, not `cRToolTip`.

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `cRTip::Init` | 0x448a40 | `sub_448a40` | `initialize_tip` | NEW -- exact body match: `gTips` fallback, main border alloc, optional `OK` / `Disable` buttons, saved `Game+0x15c`, timed auto-close rate `1/(seconds*60)` |
| `cRTip::AI` | 0x448c40 | `sub_448c40` | `update_tip` | NEW -- exact body match: hide/unhide main border, consume button clicks, auto-expire timed tips, restore saved `Game+0x15c`, call `cRTip::UnInit` |
| `cRTipManager::Init` | 0x448cf0 | `initialize_tip_manager` | -- | EXISTS |
| `cRTipManager::TipNew` | 0x448d30 | `enqueue_tip_message` | -- | EXISTS |
| `cRTipManager::AI` | 0x448d80 | `update_tip_manager` | -- | EXISTS |

---

## tMatrix Helper Family

The Android matrix method names line up cleanly with the Windows helpers exported in bundle 13:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `tMatrix::tMatrix(float, ..., float)` | 0x44cfe0 | `sub_44cfe0` | `initialize_matrix_from_values` | NEW -- direct 16-float store, exact constructor body |
| `tMatrix::RotWorldZ` | 0x44cf50 | `sub_44cf50` | `rotate_matrix_world_z` | NEW -- cos/sin mix across basis columns 0 and 1, exact Android `RotWorldZ` layout |
| `tMatrix::Multiply(const tMatrix&, const tMatrix&)` | 0x44d060 | `sub_44d060` | `multiply_matrices` | NEW -- core affine `out = lhs * rhs` helper used by both in-place multiply variants |
| `tMatrix::operator*=(const tMatrix&)` / `tMatrix::Multiply(const tMatrix&)` | 0x44d1a0 | `sub_44d1a0` | `multiply_matrix_in_place` | NEW -- wrapper copies `this` to a temp and calls the full multiply helper, matching Android `operator*=` / `Multiply` |
| `tMatrix::Identity` | 0x44d210 | `set_matrix_identity` | -- | EXISTS |
| `tMatrix::RotIdentity` | 0x44d250 | `set_matrix_identity` | `set_matrix_rotation_identity` | NEW -- resets the basis to identity while preserving translation slots |
| `tMatrix::Invert()` | 0x44d280 | `sub_44d280` | `invert_matrix_in_place` | NEW -- transpose the basis, then negate the transformed translation in place |
| `tMatrix::Invert(const tMatrix&)` | 0x44d330 | `sub_44d330` | `invert_matrix_from_source` | NEW -- writes the inverse of a source transform into a destination matrix |
| `tMatrix::Orthoganalize` | 0x44d3d0 | `sub_44d3d0` | `orthogonalize_matrix` | NEW -- normalize 3 basis vectors, then rebuild orthogonality with cross products |
| `tMatrix::LookAt(const tVector&)` | 0x44d4e0 | `sub_44d4e0` | `look_at_point` | NEW -- subtract target-position, then tailcall `SetZDir` |
| `tQuaternian::tQuaternian(const tAxis&)` | 0x44d530 | `sub_44d530` | `initialize_quaternion_from_axis` | NEW -- `xyz *= sin(angle / 2)`, `w = cos(angle / 2)` |
| `tAxis::operator=(const tQuaternian&)` | 0x44d580 | `sub_44d580` | `initialize_axis_from_quaternion` | NEW -- axis-angle unpack via `acos(w)` and `sin(theta / 2)` |
| `tQuaternian::tQuaternian(const tMatrix&)` | 0x44d5d0 | `sub_44d5d0` | `initialize_quaternion_from_matrix` | NEW -- branchy trace/diagonal quaternion constructor from matrix basis |
| `tMatrix::tMatrix(const tQuaternian&)` | 0x44d820 | `sub_44d820` | `initialize_matrix_from_quaternion` | NEW -- quaternion-to-matrix constructor with cleared translation row |
| `tMatrix::LinearInterpolate(const tMatrix&, const tMatrix&, float)` | 0x44da90 | `sub_44da90` | `linear_interpolate_matrix` | NEW -- exact Android sequence: invert / multiply / interpolate / pre-multiply / orthogonalize, then translation lerp |

---

## tVector Follow-On Helpers

These small vector helpers are used under the same camera and attachment math paths, and Android exposes the original overload split directly:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `tVector::Dot(const tVector&, const tVector&)` | 0x44cb50 | `sub_44cb50` | `dot_vectors` | NEW -- static 3D dot-product overload, used directly by `normalize_vector` |
| `tVector::Dot(const tVector&)` | 0x44cb70 | `sub_44cb70` | `dot_vector` | NEW -- member-style 3D dot-product overload used by attachment and edge helpers |
| `tVector::Multiply(const tMatrix&)` | 0x44cb90 | `sub_44cb90` | `multiply_vector_by_matrix` | NEW -- in-place affine transform that includes translation |
| `tVector::Rotate(const tMatrix&)` | 0x44cc20 | `sub_44cc20` | `rotate_vector_by_matrix` | NEW -- in-place 3x3 basis rotation without translation |
| `tVector::Normalize(const tVector&)` | 0x44cd20 | `sub_44cd20` | `normalize_vector_from_source` | NEW -- copy-and-normalize helper used by `SetZDir` before basis construction |
| `tVector::Cross(const tVector&, const tVector&)` | 0x44cd40 | `sub_44cd40` | `cross_vectors` | NEW -- shared cross-product output helper used by `SetZDir`, `Orthoganalize`, and attachment builders |

---

## Strong Implied Follow-On Names

These were not the main unresolved bundle-12 targets, but the Android call graph now makes them much less ambiguous:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `tMatrix::SetZDir(const tVector&)` | 0x44d410 | `sub_44d410` | `set_matrix_z_direction` | IMPLIED -- `sub_44d4e0` computes `target - position` and tailcalls this helper exactly like Android `LookAt` |
| `tMatrix::Interpolate(float)` | 0x44d920 | `sub_44d920` | `interpolate_matrix_rotation` | IMPLIED -- Android `LinearInterpolate` calls this exact one-arg helper between multiply and pre-multiply |
| `tMatrix::PreMultiply(const tMatrix&)` / `tMatrix::operator/=(const tMatrix&)` | 0x44d1e0 | `sub_44d1e0` | `premultiply_matrix_in_place` | IMPLIED -- this is the post-interpolate step in the Android `LinearInterpolate` implementation |

---

## Click-Start Follow-Up

Android `cRClickStart::AI` writes the player-side startup field from a game-global slot just before it transitions out of the prompt state, matching the Windows `player + 0x304 = Game + 0x1066bf4` write pattern. That does not identify the field name yet, but it strengthens the earlier bundle-12 conclusion that this slot is startup/reference-row bookkeeping rather than camera ownership.

---

## High-Value Consequences For Bundle 12

- The exact matrix-axis uncertainty is materially reduced now that `sub_44cf50` is confirmed as `tMatrix::RotWorldZ`.
- The helper behind the shared-camera blend in both `cRCameraman::AI` and `cRSubGame::CameraAI` is now confirmed as `tMatrix::LinearInterpolate`, not a bespoke game-local matrix routine.
- The full rotation-interpolation internals are now named too: Windows converts `matrix -> quaternion -> axis-angle -> scaled quaternion -> matrix`, which removes most of the remaining ambiguity around the camera blend path.
- The vector helper split is clearer too: Windows uses separate affine-transform and rotation-only vector paths, which matters when following attachment frames versus rotating pure direction vectors.
- The camera-basis build in `set_matrix_z_direction` is now explicit: normalize the target direction with `Normalize(const tVector&)`, then derive the perpendicular axes through the shared cross-product helper.
- The unresolved tip widgets are now confirmed as `cRTip` instances, which means the current port should not borrow behavior from the unrelated `cRToolTip` system.
