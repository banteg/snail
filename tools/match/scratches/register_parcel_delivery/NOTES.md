# Exact match

`register_parcel_delivery` @ 0x405040 records one parcel delivery on the
row-event display controller, awards the per-parcel score event, plays the
delivery sound, and switches directly to state 3 when the final parcel is
registered.

Two source-shape details matter:

- do not name a local copy of `delivered_parcel_count`; the direct field update
  keeps VC6 from saving `edi`;
- spell the audio calls as `g_sound_effect_manager.play_sound_effect(...)`.
  Calling the small stdcall wrapper directly has the right semantics but misses
  native's global-manager `ecx` setup.
