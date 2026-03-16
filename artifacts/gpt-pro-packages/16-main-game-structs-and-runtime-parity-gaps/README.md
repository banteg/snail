# Main Game Structs And Runtime Parity Gaps

This package is a self-contained GPT Pro handoff for the current Windows-parity gaps in the Zig port.

It bundles:
- the current port source snapshot from commit `63d4cd7137a6a0bbc1511d8a7eb4f0df17f8fc8e`
- fresh Binary Ninja exports for the functions and structs that changed our understanding most recently
- the still-relevant BN and IDA exports from bundle `15`
- a focused brief on which systems are still not fully understood, which fields still look overloaded or unsafe, and what to verify next

The main goal is not broad code review. The main goal is to tighten the semantic model of the native `Game` and `Player` owners and identify where the Zig port is still relying on plausible approximations instead of faithful behavior.

## What To Look At

Highest-priority questions:

1. Replay playback is still only partially ported.
   - We now consume the compact replay `lateral` lane directly.
   - The second saved `i16` lane (`forward`) is still unresolved.
   - Replay flag bits `0x1` and `0x2` are still unresolved.
   - Replay end still uses a port-side phase swap rather than the native fade owner.
2. The gameplay row-event display controller is still incomplete.
   - `row_event_display.state` is mapped and partially ported.
   - `row_event_display + 0x18` is still not semantically named.
   - The native writer or init path for that gate byte is still missing.
3. Some `Game` fields are still unsafe to freeze semantically.
   - `game + 0x44` is still overloaded.
   - `game + 0x48` is clearly not a global sim-rate lane, but its exact role is still not settled.
4. Parcel delivery is closer, but still not fully native.
   - Slot runtime ownership is ported.
   - Delivery flight is ported much more closely.
   - Mailbox or home-anchor vectors and some handoff details may still be wrong.
5. Attachment follow and post-follow semantics still have Windows gaps.
   - Installed-bank generation and owner pairing are still partial.
   - Some nonlinear kind-`42` entry and exit behavior may still be wrong.
6. Fall, `NoFall`, and jetpack still contain some controlled proxies.
   - The port now uses runtime flag lanes where recovered.
   - The full native world-`y` drop and hover behavior is still not fully reconstructed.

## Package Layout

- `analysis/`
  - current tracker copies and the focused ask for GPT Pro
- `binja/`
  - fresh BN decompiles and struct exports
- `binja/reports/`
  - narrow reports for the still-open gameplay lanes
- `binja/xrefs/`
  - field and helper xref evidence copied from the latest relevant RE bundle
- `ida/`
  - matching IDA pseudocode for the same gameplay cluster
- `port/`
  - current Zig source snapshot

## Suggested Reading Order

1. `analysis/investigation-brief.md`
2. `analysis/subsystem-status.md`
3. `binja/Game.txt`
4. `binja/Player.txt`
5. `binja/RowEventDisplayController.txt`
6. `binja/TrackParcelRuntime.txt`
7. `binja/0043b120-update_subgoldy.txt`
8. `binja/reports/replay-forward-lane-and-flags.txt`
9. `binja/00404cf0-update_row_event_display.txt`
10. `binja/00405040-register_parcel_delivery.txt`
11. `binja/004431d0-update_track_parcel.txt`
12. `binja/00440020-deserialize_compact_high_score_record.txt`
13. `binja/00440170-serialize_compact_high_score_record.txt`
14. `ida/0043b120-update_subgoldy.c`
15. `ida/00404cf0-update_row_event_display.c`
16. `ida/00405040-register_parcel_delivery.c`
17. `ida/004431d0-update_track_parcel.c`
18. `ida/00440020-deserialize_compact_high_score_record.c`
19. `ida/00440170-serialize_compact_high_score_record.c`

## Deliverable Requested From GPT Pro

Please do three things:

1. Identify any `Game`, `Player`, `RowEventDisplayController`, or `TrackParcelRuntime` fields that are still semantically wrong, overloaded, or too loosely named.
2. Identify any gameplay systems where the Zig port is still likely behaviorally wrong even though it now has the right overall architecture.
3. For each such issue, point to the narrowest native evidence that would let us replace the approximation with a faithful port.
