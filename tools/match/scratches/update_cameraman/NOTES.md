# Dossier — scratch not yet written (322 insns, 1274 bytes)

update_cameraman @ 0x4461d0, behind 18 camera fix commits and the 06-10
audit findings (base matrix rows, subgame-rate blend). target.asm in this
directory is the normalized reference.

From the IDA export head (full read pending next session):

- thiscall on the cameraman object; player at a member, scratch byte
  +0xcc zeroed on entry
- desired matrix seeded via `initialize_matrix_from_values(&transform,
  1,0,0,0, 0,0.946001,0.324162,0, ...)` — the audit's base rows; the
  helper returns the matrix which is qmemcpy'd into
  `cameraman->desired_matrix`
- `player->cached_camera_target_world.x * 0.4` feeds the m30 lane
- the audited subgame-rate blend (`rate * 0.3`) and the
  `fld [eax+0x2964]` player read are in the body (see
  analysis/runtime/port-parity-audit-2026-06-10.md)
- helpers to declare: initialize_matrix_from_values (returns ptr,
  many float args), matrix blend/lerp helpers — several are already
  matched (set_matrix_identity family)

Next session: read the full IDA export, map the cameraman struct
(desired_matrix offset, player member, the +0x2964 field), write the
scratch. The matched matrix helpers in the corpus should make the calls
cheap to model.
