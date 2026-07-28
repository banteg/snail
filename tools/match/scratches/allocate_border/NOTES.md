# allocate_border @ 0x4032a0

Exact border-record allocator.

The manager storage remains modeled as 150 `BorderRecord` slots with stride
`0x724`; the allocator scans `flags` at slot `+0x1a0`, stamps
`created_time` from `GameRoot::frame_counter +0x51c`, and returns the slot base at
`manager+0x684 + index*0x724`.

2026-06-20 ABI cleanup: the shared method now returns `FrontendWidget*` because
all frontend callsites consume the allocated record through that view. The
backing storage still uses `BorderRecord` for the manager layout. Focused
matcher stays exact at 23/23 instructions with 3 clean masked operands.

2026-07-11 root-owner pass: the timestamp load now uses the shared typed root
field. This independently proves `frame_counter` outside the main frame loop;
the allocator stays exact at 23/23.

2026-07-14 base ownership closure: `BorderRecord` and its returned
`FrontendWidget` semantic view now share the same inherited `BodBase`. This is
the storage relationship already proved by the exact record constructor and
the allocator's unchanged 0x724-byte stride. The allocator remains exact at
23/23 instructions with three clean operands.

## 2026-07-14 border-pool extent closure

The allocator and the exact activate/kill-all scans now share
`BORDER_RECORD_COUNT` with `BorderManager::borders`, removing three duplicated
150-slot bounds. All normalized listings remain byte-identical: allocator
`22df531ae201743dcba1c461f4f47578bfa8b59c6919e2f4b91f54894d96cafd`,
activate-all
`6f12f20db62b189b1c58331a3c45c84e60e5b9af7f22c1fe6006159e23e7b6c1`,
and kill-all
`4123e57ea4d70b7c33052dd34434df1aaa5d0cb7730d44752fd3d0da3a0d9503`.
They remain exact at 23/23, 19/19, and 14/14 instructions respectively.

## 2026-07-15 live storage/semantic replay

The shared analysis header now installs the canonical `BorderManager` and its
exact `BorderRecord[150]` pool in both databases. The allocator readback names
the flags scan, `created_time`, and `GameRoot::frame_counter`, while its return
type stays `FrontendWidget*`; no fake union collapses the two proven views.
The focused source remains exact at 23/23 with three clean operands.

## 2026-07-28 cross-port lifecycle corroboration

Android `cRBorderManager::GetBorder()` at `0x5d11c` and iOS
`cRBorderManager::GetBorder()` at `0x388a0` independently preserve the same
150-slot allocation lifecycle. Each scans the slot flags at mobile
record-relative `+0x194`, stamps the immediately preceding `+0x190` lane from
the mobile root frame counter, and returns the record base. Windows remains
authoritative for its own layout: this exact allocator scans
`BorderRecord::flags +0x1a0`, stamps `created_time +0x19c` from
`GameRoot::frame_counter +0x51c`, and returns that same base through
`FrontendWidget*`.

The semantic `FrontendWidget` view now names `created_time` as well as the
backing `BorderRecord` view. The mobile/Windows `0xc` offset delta is recorded
as layout evidence only; no mobile address was copied into the Windows type.
