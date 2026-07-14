# Exact match

`register_parcel_delivery` @ 0x405040 is the exact Windows
`Completion::register_parcel_delivery` / cross-port
`cRCompletion::RegisterParcel`. It records one parcel delivery on the
embedded completion owner, awards the per-parcel score event, plays the
delivery sound, and switches directly to state 3 when the final parcel is
registered.

Two source-shape details matter:

- do not name a local copy of `delivered_parcel_count`; the direct field update
  keeps VC6 from saving `edi`;
- spell the audio calls as `g_sound_effect_manager.play_sound_effect(...)`.
  Calling the small stdcall wrapper directly has the right semantics but misses
  native's global-manager `ecx` setup.

The 0x50-byte `Completion` is the single owner for parcel display and final
result phases. Consolidating the former row-event view remains exact at 36/36
with all 10 operands clean.

Both score awards now name the embedded `GameRoot::subgame.player` producer
instead of reconstructing `Player*` from `root + 0x42fd7c`. The direct global
reloads and exact 36/36 code shape are unchanged.

## 2026-07-14 completion lifecycle ownership

The final delivery now enters `COMPLETION_STATE_SUMMARY_PENDING`, which the
exact AI member consumes to reveal the summary and continue prompt. Focused
matching remains exact at 36/36 instructions with all 10 operands clean.
