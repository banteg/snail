# update_voice_set @ 0x449360

The exact Windows member is the authored `cRVoiceSet::AI()` retained by
Android. Both bodies use the same `+0x10` cooldown and `+0x14` step fields:
an active cooldown advances once per update and clears after crossing `1.0f`.
The shared body also confirms the `void` contract.

Focused Windows matching remains exact at 14/14 instructions with two clean
masked operands. Mobile evidence is used for ownership and field provenance;
it does not alter the matching source.

## 2026-08-09 authored source promotion

The matcher now spells the body `cRVoiceSet::AI()` and binds
`?AI@cRVoiceSet@@QAEXXZ`. The stable function directory remains
`update_voice_set`; focused matching stays exact at 14/14 instructions with
two clean operands.
